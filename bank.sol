// SPDX-License-Identifier: MIT
pragma solidity ^0.8.0;

contract BankAccount {
    // State variable to keep track of the customer's balance
    uint256 private balance;

    // Event to log deposits and withdrawals
    event Deposit(uint256 amount);
    event Withdraw(uint256 amount);

    // Constructor to initialize the balance to zero upon deployment
    constructor() {
        balance = 0;
    }

    // Function to deposit money into the account
    function deposit() public payable {
        balance += msg.value; // Update balance with the sent amount
        emit Deposit(msg.value); // Emit deposit event
    }

    // Function to withdraw money from the account
    function withdraw(uint256 amount) public {
        require(amount <= balance, "Insufficient balance"); // Check for sufficient balance
        balance -= amount; // Deduct amount from balance
        payable(msg.sender).transfer(amount); // Send amount to the caller
        emit Withdraw(amount); // Emit withdrawal event
    }

    // Function to check the current balance
    function getBalance() public view returns (uint256) {
        return balance;
    }
}