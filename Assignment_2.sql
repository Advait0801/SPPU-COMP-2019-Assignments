/*
Assignment No 2A  (Student Schema)
Consider the following relational Schema.  
 Student( s_id,Drive_id,T_id,s_name,CGPA,s_branch,S_dob)
 PlacementDrive( Drive_id,Pcompany_name,package,location)
 Training ( T_id,Tcompany_name,T_Fee,T_year) 
Note: Use referential integrity constraints while creating tables with on delete cascade options. 
Create view(simple), index, sequence and synonym based on above tables.

Name : Advait Naik
Roll No : 31352
*/


-- creating tables
create table Student(
    RollNo int auto_increment primary key,
    DriveId int,
    TrainingId int,
    StudentName varchar(30),
    CGPA float,
    Branch varchar(5),
    foreign key(Driveid) references PlacementDrive(Driveid),
	foreign key(TrainingId) references Training(TrainingId)
);

create table PlacementDrive(
    DriveId int auto_increment primary key,
    CompanyName varchar(30),
    Package int,
    CompanyLocation varchar(30)
);

create table Training(
    TrainingId int auto_increment primary key,
    CompanyName varchar(30),
    Fees int,
    TrainingYear year
);


-- inserting values into tables
insert into Student(DriveId,TrainingId,StudentName,CGPA,Branch)
values
    ( 1 , 3 , 'Advait Naik' , 8.7 , 'CE' ),
    ( 1 , 2 , 'Shubham Panchal' , 9.1 , 'CE' ),    
    ( 3 , 2 , 'Kaustubh Netke' , 7.3 , 'CE' ),
    ( 2 , 2 , 'Aarya Ghate' , 8.1 , 'IT' ),
    ( 1 , 4 , 'Manthan Adhav' , 9.3 , 'IT' ),
    ( 4 , 1 , 'Anish Khare' , 6.5 , 'ENTC' ),
    ( 3 , 3 , 'Sagar Akhade' , 6.8 , 'ENTC' ),
    ( 5 , 5 , 'Rhea Shah' , 7.2 , 'CE' ),
    ( 5 , 2 , 'Srushti Kulkarni' , 8.8 , 'IT'),
    ( 4 , 4 , 'Ridhima Sinare' , 8.4 , 'CE' );

insert into PlacementDrive(CompanyName,Package,CompanyLocation)
values
    ( 'Imocha' , 20 , 'Pune' ) ,
    ( 'Barclays' , 6 , 'Pune' ) , 
    ( 'TraceLink' , 50 , 'Mumbai' ) , 
    ( 'Mastercard' , 40 , 'Banglore' ) , 
    ( 'Google' , 30 , 'Mumbai' ) ;

insert into Training(CompanyName,Fees,TrainingYear)
values
    ( 'Imocha' , 2000 , '2020' ) ,
    ( 'Barclays' , 500 , '2022' ) , 
    ( 'TraceLink' , 350 , '2021' ) , 
    ( 'Mastercard' , 230 , '2019' ) , 
    ( 'Google' , 5000 , '2019' ) ;


-- Queries:
-- 2. Display all students details with branch ‘Computer ‘and ‘It’ and student name starting with  'a' or 'd'.
select * from Student where (Branch='CE' || Branch='IT') && (StudentName like 'A%' || StudentName like 'D%');

-- 3. list the number of different companies.(use of distinct)
select distinct CompanyName from PlacementDrive;

-- 4. Give 15% increase in fee of the Training  whose joining year is 2019.
select CompanyName, Fees*1.15 as Fees, TrainingYear from Training where TrainingYear='2019'; 

-- 5. Delete Student details having CGPA score less than 7.
delete from Student where CGPA < 7.0

-- 6. Find the names of companies belonging to Pune or Mumbai
select CompanyName from PlacementDrive where (CompanyLocation='Pune' || CompanyLocation='Mumbai');

-- 7. Find the student name who joined training in  1-1-2019 as well as in 1-1-2021 
select s.StudentName from Student s, Training t where t.TrainingYear='2019' || t.TrainingYear='2021';

-- 8. Find the student name  having maximum CGPA score and names of students  having CGPA score between  7 to 9 .
select s.StudentName, max(CGPA) from Student s where s.CGPA between 7.0 and 9.0;

-- 9. Display all Student  name with T_id  with decreasing order of Fees
select s.StudentName, t.TrainingId from Student s,Training t order by t.Fees desc;

-- 10. Display Company name, S_name ,location and Package with Package  30K, 40K and 50k 
select s.StudentName, pd.CompanyName, pd.CompanyLocation, pd.Package from Student s inner join PlacementDrive pd on s.DriveId = pd.DriveId where pd.Package in( 30 , 40 , 50 ) ; 


-- Indexing and views
-- Simple index
create index s_name on Student(StudentName);
explain select * from Student where (StudentName like 'A%');

-- Composite index
create index training_name on Training(CompanyName,TrainingYear);

-- Unique index
create unique index placement_package on PlacementDrive(Package);

-- Text Search index
create index student_name on Student(StudentName(10));

-- views
create view comp as select * from Student where branch='CE';
create view pune as select * from PlacementDrive where CompanyLocation='Pune';
select * from comp;
select * from pune;