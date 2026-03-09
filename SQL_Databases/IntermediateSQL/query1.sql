-- Write the query to create the 4 tables below.
CREATE TABLE client (
    id INT(11) AUTO_INCREMENT,
    first_name VARCHAR(255) NOT NULL,
    last_name VARCHAR(255) NOT NULL,
    email VARCHAR(255) NOT NULL,
    PRIMARY KEY (id),
    UNIQUE (first_name, last_name)
);

CREATE TABLE employee (
    id INT(11) AUTO_INCREMENT,
    first_name VARCHAR(255) NOT NULL,
    last_name VARCHAR(255) NOT NULL,
    start_date DATE NOT NULL,
    email VARCHAR(255) NOT NULL,
    PRIMARY KEY (id),
    UNIQUE (first_name, last_name)
);
CREATE TABLE project (
    id int(11) AUTO_INCREMENT,
    title varchar(255) NOT NULL,
    comments text,
    cid int,
    PRIMARY KEY (id),
    CONSTRAINT FK_client_id FOREIGN KEY (cid)
    REFERENCES client(id),
    UNIQUE (title)
);

CREATE TABLE works_on (
    pid int,
    eid int,
    due_date date NOT NULL,
    PRIMARY KEY (eid, pid),
    CONSTRAINT FK_project_id FOREIGN KEY (pid)
    REFERENCES project(id),
    CONSTRAINT FK_employee_id FOREIGN KEY (eid)
    REFERENCES employee(id)
);


