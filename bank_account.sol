// SPDX-License-Identifier: MIT
pragma solidity ^0.8.0;

contract BankAccount {
    address public owner; // The owner of the bank account
    uint256 public balance; // The balance of the account

    constructor() {
        owner = msg.sender;
    }

    modifier onlyOwner() {
        require(msg.sender == owner, "Only the owner can perform this operation");
        _;
    }

    function deposit(uint256 amount) public onlyOwner {
        require(amount > 0, "Amount to deposit must be greater than 0");
        balance += amount;
    }

    function withdraw(uint256 amount) public onlyOwner {
        require(amount > 0, "Amount to withdraw must be greater than 0");
        require(balance >= amount, "Insufficient balance");
        balance -= amount;
    }

    function getBalance() public view returns (uint256) {
        return balance;
    }
}