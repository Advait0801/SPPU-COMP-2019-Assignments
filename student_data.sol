// SPDX-License-Identifier: MIT
pragma solidity ^0.8.0;

contract StudentData {
    struct Student {
        string name;
        uint256 age;
    }

    Student[] public students; // Array to store student data

    event StudentAdded(string name, uint256 age);

    // Fallback function to accept Ether
    receive() external payable {}

    // Add a new student to the array
    function addStudent(string memory _name, uint256 _age) public {
        Student memory newStudent = Student(_name, _age);
        students.push(newStudent);
        emit StudentAdded(_name, _age);
    }

    // Get the number of students
    function getStudentCount() public view returns (uint256) {
        return students.length;
    }

    // Get student data by index
    function getStudent(uint256 index) public view returns (string memory, uint256) {
        require(index < students.length, "Student does not exist");
        Student memory student = students[index];
        return (student.name, student.age);
    }
}