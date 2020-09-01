#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) noexcept : QMainWindow(parent), iterator(history)
{
    this->company = nullptr;
    this->currentDepartment = nullptr;
    this->centralWidget = new CentralWidget();
    setCentralWidget(this->centralWidget);
    this->centralWidget->setEnabled(false);
    statusBar()->show();
    createActions();

    connect(this->centralWidget, &CentralWidget::currentDepartment, this, &MainWindow::setCurrentDepartment);
    connect(this->centralWidget, &CentralWidget::currentEmployee, this, &MainWindow::setCurrentEmployee);
    connect(this->centralWidget, &CentralWidget::addDepartment, this, &MainWindow::addDepartment);
    connect(this->centralWidget, &CentralWidget::addEmployee, this, &MainWindow::openNewEployeeDialog);
    connect(this->centralWidget, &CentralWidget::removeEmployee, this, &MainWindow::removeEmployee);
    connect(this->centralWidget, &CentralWidget::removeDepartment, this, &MainWindow::removeDepartment);
    connect(this->centralWidget, &CentralWidget::editDepartment, this, &MainWindow::editDepartment);
    connect(this->centralWidget->view(), &QTreeView::doubleClicked,this, &MainWindow::editCompany);
}

void MainWindow::createActions()
{
    QMenu *fileMenu = menuBar()->addMenu(tr("&Файл"));

    QAction *open= new QAction(tr("Открыть"));
    open->setShortcuts(QKeySequence::Open);
    open->setStatusTip(tr("Открыть файл"));
    connect(open, &QAction::triggered, this, &MainWindow::openFile);
    fileMenu->addAction(open);

    QAction *create = new QAction(tr("Создать"));
    create->setShortcuts(QKeySequence::New);
    create->setStatusTip(tr("Создать новый файл"));
    connect(create, &QAction::triggered, this, &MainWindow::openNewCompanyDialog);
    fileMenu->addAction(create);

    QAction *save = new QAction(tr("Сохранить"));
    save->setShortcuts(QKeySequence::Save);
    save->setStatusTip(tr("Сохранить файл"));
    connect(save, &QAction::triggered, this, &MainWindow::saveFile);
    fileMenu->addAction(save);

    QAction *undo = new QAction(tr("Отменить"));
    undo->setShortcuts(QKeySequence::Undo);
    undo->setStatusTip(tr("Отмена действия"));
    connect(undo, &QAction::triggered, this, &MainWindow::undoCommand);
    fileMenu->addAction(undo);

    QAction *redo = new QAction(tr("Повторить"));
    redo->setShortcuts(QKeySequence::Redo);
    redo->setStatusTip(tr("Повтор отмененного действия"));
    connect(redo, &QAction::triggered, this, &MainWindow::redoCommand);
    fileMenu->addAction(redo);
}

void MainWindow::addEmployee()
{
    QStringList data = this->employeeEditor->getData();
    if(this->company->getDepartments()->value(this->currentDepartment->getName())->getEmployees()
            ->value(Employee::getId(data[0], data[1], data[2], data[3], data[4].toUInt())) != 0)
    {
        this->statusBar()->showMessage("Такой работник уже существует");
        return;
    }
    CommandAddEmployee* command = new CommandAddEmployee(this->company, this->currentDepartment,
                            data[0], data[1], data[2], data[3], data[4].toUInt());
    executeCommand(command);
}

void MainWindow::editCompany(const QModelIndex &index)
{
    QStandardItem* item = this->company->itemFromIndex(index.siblingAtColumn(0));
    if(index.parent() != QModelIndex())
    {
        this->currentEmployee = static_cast<Employee*>(item);
        this->employeeEditor = new EmployeeEditor(this->currentEmployee);
        this->employeeEditor->show();
        connect(this->employeeEditor, &EmployeeEditor::accepted, this, &MainWindow::editEmployee);
    }
}

void MainWindow::editEmployee()
{
    QStringList data = this->employeeEditor->getData();
    if(this->company->getDepartments()->value(this->currentDepartment->getName())->getEmployees()
            ->value(Employee::getId(data[0], data[1], data[2], data[3], data[4].toUInt())) != 0)
    {
        this->statusBar()->showMessage("Такой работник уже существует");
        return;
    }

    CommandEditEmployee* command = new CommandEditEmployee(this->company, this->currentDepartment,
                    this->currentEmployee, data[0], data[1], data[2], data[3], data[4].toUInt());
    executeCommand(command);
    if(this->employeeEditor != nullptr)
    {
        this->employeeEditor->disconnect();
        this->employeeEditor->deleteLater();
    }
    this->centralWidget->setDep(this->currentDepartment->getName(),
                this->currentDepartment->getCountEmployees(), this->currentDepartment->getAverageSalary());
}

void MainWindow::removeEmployee()
{
    CommandRemoveEmployee* command = new CommandRemoveEmployee(this->company, this->currentDepartment, this->currentEmployee);
    executeCommand(command);
}

void MainWindow::openFile()
{
    this->path = QFileDialog::getOpenFileName(this, tr("Open File"), ".", tr("XML files (*.xml)"));
    QFile xmlFile(path.toString());
    if(!this->path.isEmpty() && xmlFile.open(QIODevice::ReadOnly))
    {
        QXmlStreamReader reader(&xmlFile);
        QString depName;
        QString name;
        QString surname;
        QString middleName;
        QString function;
        uint32_t salary;
        while (!reader.atEnd() && reader.readNext())
        {
            if(reader.isStartElement())
            {
                if(reader.name() == "departments"){
                    newCompany();
                } else if(reader.name() == "department") {
                    depName = reader.attributes().value("name").toString().trimmed();
                    if(depName.isEmpty()){
                        this->currentDepartment = this->company->addDepartment("Неизвестный отдел");
                    }else{
                        this->currentDepartment = this->company->addDepartment(depName);
                    }
                }else if(reader.name() == "employment"){
                    for (int i = 0; i < 5; ++i)
                    {
                        reader.readNextStartElement();
                        if( reader.name() == "name"){
                            name = reader.readElementText();
                            if(name.isEmpty())
                                name = "No Data";
                        }else if (reader.name() == "surname"){
                            surname = reader.readElementText();
                        }else if (reader.name() == "middleName"){
                            middleName = reader.readElementText();
                        }else if (reader.name() == "function"){
                            function = reader.readElementText();
                        }else if (reader.name() == "salary"){
                            salary = reader.readElementText().toInt();
                        }
                    }
                    this->currentDepartment->addEmployee(name, surname, middleName, function, salary);
                }
            }
        }
    }
}

void MainWindow::saveFile()
{
    if(this->company)
    {
        QFile xmlFile(this->path.toString());
        if(xmlFile.open(QIODevice::WriteOnly))
        {
            QXmlStreamWriter writer(&xmlFile);
            writer.setAutoFormatting(true);
            if(!this->company->getDepartments()->isEmpty()){
                writer.writeStartDocument();
                writer.writeStartElement("departments");

                QMapIterator<QString, Department*> iter (*(this->company)->getDepartments());

                while(iter.hasNext())
                {
                    iter.next();
                    Department *department = iter.value();
                    writer.writeStartElement("department");
                    writer.writeAttribute("name", department->getName());
                    QMapIterator<int, Employee*> iterator (*department->getEmployees());
                    writer.writeStartElement("employments");
                    while(iterator.hasNext())
                    {
                        iterator.next();
                        Employee* employee = iterator.value();
                        writer.writeStartElement("employment");
                        writer.writeTextElement("surname", employee->getSurname());
                        writer.writeTextElement("name", employee->getName());
                        writer.writeTextElement("middleName", employee->getMiddleName());
                        writer.writeTextElement("function", employee->getFunction());
                        writer.writeTextElement("salary", QString::number(employee->getSalary()));
                        writer.writeEndElement();
                    }
                    writer.writeEndElement();
                    writer.writeEndElement();
                }
                writer.writeEndElement();
                writer.writeEndDocument();
                xmlFile.close();
            }else{
                writer.writeStartDocument();
                writer.writeEndDocument();
                xmlFile.close();
            }
        }
    }
}

void MainWindow::openNewCompanyDialog()
{
    this->path = QFileDialog::getSaveFileName(this, tr("Save Xml"), ".", tr("Xml files (*.xml)"));
    if(this->path.isValid()){
        if(this->company){
            saveFile();
            newCompany();
        }else{
            saveFile();
            delete this->company;
            clearHistory();
            newCompany();
        }
    }
}

void MainWindow::newCompany()
{
    if(!this->history.isEmpty())
        clearHistory();
    this->company = new Company();
    this->centralWidget->view()->setModel(company);
    this->centralWidget->setEnabled(true);
    connect(this->centralWidget->view()->selectionModel(), &QItemSelectionModel::selectionChanged, this->centralWidget, &CentralWidget::setEnableButtons);
}

void MainWindow::openNewEployeeDialog()
{
    this->employeeEditor = new EmployeeEditor();
    connect(this->employeeEditor, &EmployeeEditor::accepted, this, &MainWindow::addEmployee);
    this->employeeEditor->show();
}

void MainWindow::setCurrentDepartment(const QModelIndex &index)
{
    this->currentDepartment = static_cast<Department*>(this->company->itemFromIndex(index));
    this->centralWidget->setDep(this->currentDepartment->getName(), this->currentDepartment->getCountEmployees(),
                                this->currentDepartment->getAverageSalary());
}

void MainWindow::setCurrentEmployee(const QModelIndex &index)
{
    this->currentEmployee = static_cast<Employee*>(this->company->itemFromIndex(index));
}

void MainWindow::addDepartment(QString name)
{
    if(name.isEmpty())
    {
        this->statusBar()->showMessage("Введите название департамента");
        return;
    }
    if(!this->company->getDepartments()->count(name)){
        CommandAddDepartment* command = new CommandAddDepartment (this->company, name);
        executeCommand(command);
    }else{
        this->statusBar()->showMessage("Недопустимая операция, такой отдел существует");
    }
}

void MainWindow::editDepartment(QString name)
{
    if(name.isEmpty())
    {
        this->statusBar()->showMessage("Введите название департамента");
        return;
    }
    if(!this->company->getDepartments()->count(name)){
        CommandEditDepartment* command = new CommandEditDepartment(this->company, this->currentDepartment, name);
        executeCommand(command);
        this->centralWidget->setDep(this->currentDepartment->getName(), this->currentDepartment->getCountEmployees(),
                                    this->currentDepartment->getAverageSalary());
    }else{
        this->statusBar()->showMessage("Недопустимая операция, такой отдел существует");
    }
}

void MainWindow::removeDepartment()
{
    CommandRemoveDepartment* command = new CommandRemoveDepartment(company, currentDepartment);
    executeCommand(command);
}

void MainWindow::executeCommand(Command *command)
{
    command->execute();
    this->history.append(command);
    this->iterator = this->history;
    this->iterator.toBack();
}

void MainWindow::undoCommand()
{
    if(!this->history.isEmpty())
        if(this->iterator.hasPrevious())
        {
            this->iterator.previous()->undo();
            this->centralWidget->setDep(this->currentDepartment->getName(),
                    this->currentDepartment->getCountEmployees(), this->currentDepartment->getAverageSalary());
        }
}

void MainWindow::redoCommand()
{
    if(!this->history.isEmpty())
        if(this->iterator.hasNext())
        {
            this->iterator.next()->execute();
            this->centralWidget->setDep(this->currentDepartment->getName(),
                    this->currentDepartment->getCountEmployees(), this->currentDepartment->getAverageSalary());
        }
}

void MainWindow::clearHistory()
{
    for (this->iterator.toFront(); this->iterator.hasNext();)
        delete this->iterator.next();
    this->history.clear();
}

MainWindow::~MainWindow() noexcept
{
    saveFile();
    this->centralWidget->disconnect();
    clearHistory();
    delete this->company;
}
