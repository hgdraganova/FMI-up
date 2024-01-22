// UPpr_23-24_fn8MI0600329_KP6.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
/**
*
* Solution to course project # 6
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2023/2024
*
* @author Hrisimira Draganova
* @idnumber 8MI0600329
* @compiler  VC
*
* SHA-256
*
*/


#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <iomanip>
#include <openssl/sha.h>

// Function to hash a message using SHA-256
std::string sha256(const std::string& message)
    {
    unsigned char digest[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    void SHA256_Init(SHA256_CTX &sha256);
    void SHA256_Update(SHA256_CTX & sha256, const std::string & message);
    void SHA256_Final(unsigned char digest, SHA256_CTX & sha256);

    std::stringstream ss;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i)
    {
        ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(digest[i]);
    }
    return ss.str();
    }

//Function to save a  hashed message to a file
void saveHashToFile(const std::string& hash, const std::string& filename)
{
    std::ofstream file(filename);
    if (file.is_open())
    {
        file << hash;
        file.close();
        std::cout << "Hashed text saved to " << filename << std::endl;
    }
    else
    {
        std::cerr << "Error writing to file " << filename << std::endl;
    }
}

//Function to verify a hash
bool verifyHash(const std::string& message, const std::string& hash)
{
    return sha256(message) == hash;
}

//Function to handle option 1: Hash a message 
void option1()
{
    int subChoice;
    std::cout << "Choose an option:\n";
    std::cout << "1. Enter text manually\n";
    std::cout << "2. Read text from a file\n";
    std::cin >> subChoice;
    std::cin.ignore(); //Clear the newline character after entering the choice
    std::string message;

    if (subChoice == 1)
    {
        std::cin.ignore(); //Clear the newline before reading text
        std::cout << "Enter the text to hash: ";
        getline(std::cin, message);
    }
    else if (subChoice == 2)
    {
        std::string filename;
        std::cout << "Enter the filename to read from: ";
        std::cin >> filename;
        std::ifstream file(filename);
        if (file.is_open())
        {
            getline(file, message);
            file.close();
        }
        else
        {
            std::cerr << "Error opening file" << filename << std::endl;
            return;
        }
    }
    else
    {
        std::cerr << "Invalid choice\n";
        return;
    }

        std::string hash = sha256(message);
        std::cout << "SHA-256 hash: " << hash << std::endl;
}

//Function to handle option 2: Save a hash to a file
void option2()
{
    std::cout << "Enter the text to hash: ";
    std::string message;
    std::cin.ignore(); //Clear the newline before reading text
    getline(std::cin, message);
    std::string hash = sha256(message);
    std::string filename;
    std::cout << "Enter the filename to save to: ";
    getline(std::cin, filename);
    saveHashToFile(hash, filename);
}

//Function to handle option 3: Verify a hash
void option3()
{
    std::cout << "Enter the hash to verify: ";
    std::string hash;
    std::cin.ignore(); //Clear the newline before reading text
    getline(std::cin, hash);
    std::cout << "Enter the text to compare: ";
    std::string message;
    getline(std::cin, message);

    if (verifyHash(message, hash))
    {
        std::cout << "The hash matches\n";
    }
    else 
    {
        std::cout << "The hash does not match\n";
    }
}

int main()
{
    int choice;
    std::cout << "Choose an option:\n";
    std::cout << "1. Hash a message\n";
    std::cout << "2. Save a hash to a file\n";
    std::cout << "3. Verify a hash\n";
    std::cin >> choice;
    std::cin.ignore(); //Clear the newline character after entering the choice

    switch (choice)
    {
    case 1:
        option1();
        break;
    case 2:
        option2();
        break;
    case 3:
        option3();
        break;
    default:
        std::cerr << "Invalid choice.\n";
        return 1;
    }
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
