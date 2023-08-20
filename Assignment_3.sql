/*
Assignment No 3A  (Student Schema)
Consider the following relational Schema.  
 Student( s_id,Drive_id,T_id,s_name,CGPA,s_Branch,S_dob)
 PlacementDrive( Drive_id,PCompanyName,package,CompanyLocation)
 Training ( T_id,TCompanyName,T_Fees,T_year) 
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
    CompanyCompanyLocation varchar(30)
);

create table Training(
    TrainingId int auto_increment primary key,
    CompanyName varchar(30),
    Feess int,
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

insert into PlacementDrive(CompanyName,Package,CompanyCompanyLocation)
values
    ( 'Imocha' , 20 , 'Pune' ) ,
    ( 'Barclays' , 6 , 'Pune' ) , 
    ( 'TraceLink' , 50 , 'Mumbai' ) , 
    ( 'Mastercard' , 40 , 'Banglore' ) , 
    ( 'Google' , 30 , 'Mumbai' ) ;

insert into Training(CompanyName,Feess,TrainingYear)
values
    ( 'Imocha' , 2000 , '2020' ) ,
    ( 'Barclays' , 500 , '2022' ) , 
    ( 'TraceLink' , 350 , '2021' ) , 
    ( 'Mastercard' , 230 , '2019' ) , 
    ( 'Google' , 5000 , '2019' ) ;


-- Queries
-- 1. Find the Student details and Placement details using NATURAL JOIN.  
select * from Student natural join PlacementDrive;

-- 2. Find all the student details with CompanyName who have conducted in same drive
select s.*, pd.CompanyName from Student s inner join PlacementDrive pd on s.DriveId = pd.DriveId;

-- 3. List all the Student name and Student Branch of Student having package 5 LPA
select s.StudentName,s.Branch from Student s inner join PlacementDrive pd on s.DriveId = pd.DriveId where pd.Package = 5;

-- 4.List all the student names ,CompanyName having T_Fees more than 20000
select s.StudentName,t.CompanyName from Student s inner join Training t on s.TrainingId = t.TrainingId where t.Fees > 500;

-- 5. Display all Training details attended by “shantanu” in year 2011  
select t.* from Student s inner join Training t on s.TrainingId = t.TrainingId where s.StudentName = 'Advait Naik' && t.TrainingYear = '2019'; 

-- 6. list the total number of companies who conduct Training before 2015
select count(CompanyName) from Training where Training.TrainingYear < 2019;

-- 7. List the Student name with company ‘Microsoft’ and  CompanyLocation ’Thane’
select s.* from Student s inner join PlacementDrive pd on s.DriveId = pd.DriveId where pd.CompanyLocation in( 'Mumbai' , 'Pune' ) ;

-- 8. Find the names of all Students who have joined ‘Microsoft ‘ Training  in 2015 .
select s.StudentName from Student s inner join Training t on s.TrainingId = t.TrainingId where t.CompanyName = 'Google' ;

-- 9. Create a view showing the Student and Training details.  
create view student_Training_view as select s.*, t.CompanyName, t.Fees, t.TrainingYear from Student s inner join Training t on s.TrainingId = t.TrainingId;

-- 10. Perform Manipulation on simple view-Insert, update, delete, drop view.  
insert into student_Training_view(DriveId, TrainingId, StudentName, CGPA, Branch ) values( 2 , 2 , 'Advait Naik' , 8.5 , 'CE' ) ; 
insert into student_Training_view( CompanyName, Fees, TrainingYear ) values( 'BNY Mellon' , 20 , '2019' ) ;