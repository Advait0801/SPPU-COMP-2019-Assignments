create table student_marks(
    name varchar(20),
    marks int
) ; 

create table result(
    name varchar(20),
    rollno int,
    marks int
) ;

-- procedure
delimiter #
create procedure grades(IN name varchar(20))
begin
declare n varchar(20);
declare m int;
declare category varchar(20);

set n = name;
select marks into m from student_marks where student_marks.name = n;

if m>=990 and m <=1500 then
    set category = 'distinction';
else if m>=899 and m<990 then 
    set category  = 'first_class';
else if m>=825 and m<=899 then
    set category = 'high second class' ;
end if;

update result set class = category where result.name = n;

end
#