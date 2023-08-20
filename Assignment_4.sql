/*
Write a procedure to calculate area of circle for a value of radius varying from 5 to 9. Store the radius and the corresponding values of calculated area in an empty table named areas, consisting of 2 columns, radius and area.

Name : Advait Naik
Rollno : 31352
*/


-- create table
create table areas(
    radius int,
    area float
);


-- procedure
delimiter #
create procedure calc(in radius INT)
begin
declare r INT;
declare a FLOAT;
set r = radius;
if r >= 5 and r <= 9 then
    set a = 3.14 * r *r;
    insert into areas(radius,area) values(r,a);
end
#
delimiter ;

