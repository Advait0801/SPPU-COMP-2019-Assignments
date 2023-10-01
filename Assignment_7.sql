-- create tables
create table library(
    id int auto_increment primary key,
    name varchar(20),
    price int
);

create table audit_course(
    id int auto_increment primary key,
    name varchar(20),
    price int    
);


-- inserting values
insert into library(name,price)
values('SPOS' , 100),
('CN' , 200),
('DELD' , 300),
('DBMS' , 100),
('BXE' , 900),
('DS' , 1200);


-- triggers
create trigger deleted_trigger
before delete on library
for ech row 
insert into audit_course values(old.id, old.name, old.price);

create trigger updated_trigger
before update on library
for each row
insert into audit_course values(old.id, old.name, old.price);