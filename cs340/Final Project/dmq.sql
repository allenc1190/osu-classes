-- These are some Database Manipulation queries for a partially implemented Project Website 
-- using the bsg database.
-- Your submission should contain ALL the queries required to implement ALL the
-- functionalities listed in the Project Specs.


-- -----------------ACCOUNTS------------------------
-- Initial Select for Accounts
SELECT * FROM Accounts;
-- Filter/Search Select for Accounts
SELECT * FROM Accounts WHERE Account_id = :accounts_account_id_search AND Username = :accounts_username_search AND Email = :accounts_email_search;
-- Add Row for Accounts
INSERT INTO Accounts VALUES (:accounts_account_id_add, :accounts_username_add, :accounts_email_add);
-- Delete Row for Accounts
DELETE FROM Accounts WHERE Account_id = :accounts_account_id_search;
-- Update Row for Accounts
UPDATE Accounts SET Username = :accounts_username_search, Email = :accounts_email_search WHERE Account_id = :accounts_account_id;

-- -----------------POSTS------------------------
-- Initial Select for Posts
SELECT * FROM Posts
-- Filter/Search Select for Posts
SELECT * FROM Posts WHERE Post_id = :posts_post_id_search AND Text = :posts_text_search AND Account_id = :posts_account_id_search AND Timestamp = :posts_timestamp_search;
-- Add Row for Posts
INSERT INTO Posts VALUES (:posts_post_id_add, :posts_text_id_add, :posts_account_id_add, :posts_timestamp_add);
-- Delete Row for Posts
DELETE FROM Posts WHERE Post_id = :posts_post_id_search;
-- Update Row for Posts
UPDATE Posts SET Text = :posts_text_search, Account_id = :posts_account_id_search, Timestamp = :posts_timestamp_search WHERE Post_id = :posts_post_id;

-- -----------------COMMENTS------------------------
-- Initial Select for Comments
SELECT * FROM Comments
-- Filter/Search Select for Comments
SELECT * FROM Comments WHERE Comment_id = :comments_id_search AND Account_id = :comments_account_id_search AND Post_id = :comments_post_id_search, AND Text = :comments_text_search and Timestamp = :comments_timestamp_search;
-- Add Row for Comments
INSERT INTO Comments VALUES (:comments_comment_id_add, :comments_account_id_add, :comments_post_id_add, :comments_text_add, :comments_timestamp_add);
-- Delete Row for Comments
DELETE FROM Comments WHERE Comment_id = :comments_comment_id_search;
-- Update Row for Comments
UPDATE Comments SET Account_id = :comments_account_id_search, Post_id = :comments_post_id_search, Text = :comments_text_search WHERE Comment_id = :comments_comment_id_search;

-- -----------------GROUPS------------------------
-- Initial Select for Groups
SELECT * FROM Groups;
-- Filter/Search Select for Groups
SELECT * FROM Groups WHERE Group_id = :groups_group_id_search AND Group_name = :groups_group_name_search;
-- Add Row for Groups
INSERT INTO Groups VALUES (:groups_group_id_add, :groups_group_name_add);
-- Delete Row for Groups
DELETE FROM Groups WHERE Group_id = :groups_group_id_search;
-- Update Row for Groups
UPDATE FROM Groups SET Group_name = :groups_group_name WHERE Group_id;

-- -----------------MEMBERSHIPS------------------------
-- Initial Select for Memberships
SELECT * FROM Memberships;
-- Filter/Search Select for Memberships
SELECT * FROM Memberships WHERE Group_id = :memberships_group_id_search AND Account_id = :memberships_account_id_search;
-- Add Row for Memberships
INSERT INTO Memberships VALUES (:memberships_account_id_add, :memberships_group_id_add);
-- Delete Row for Memberships
DELETE FROM Memberships WHERE Group_id = :memberships_group_id_search;
-- Update Row for Memberships
UPDATE Memberships SET Group_name = :memberships_group_name WHERE Group_id;

-- -----------------MESSAGES------------------------
-- Initial Select for Messages
SELECT * FROM Messages
-- Filter/Search Select for Messages
SELECT * FROM Messages WHERE Message_id = :messages_message_id_search AND Account_id = :messages_account_id_search AND Group_id = :messages_group_id_search AND Message = :messages_text_search AND Timestamp = :messages_timestamp_search;
-- Add Row for Messages
INSERT INTO Messages VALUES (:messages_message_id_add, :messages_account_id_add, :messages_group_id_add, :messages_text_add, :messages_timestamp_add);
-- Delete Row for Messages
DELETE FROM Messages WHERE Message_id = :messages_comment_id_search;
-- Update Row for Messages
UPDATE Messages SET Account_id = :messages_account_id_search, Group_id = :messages_group_id_search, Text = :messages_text_search WHERE Message_id = :messages_message_id_search;


-- -----------------FRIENDSHIPS------------------------
-- Initial Select for Friendships
SELECT * FROM Friendships;
-- Filter/Search Select for Friendships
SELECT * FROM Friendships WHERE From_Account_id = :friendships_From_Account_id_search AND To_Account_id = :friendships_To_Account_id_search;
-- Add Row for Friendships
INSERT INTO Friendships VALUES (:friendships_From_Account_id_add, :friendships_To_Account_id_add);
-- Delete Row for Friendships
DELETE FROM Friendships WHERE From_Account_id = :friendships_From_Friend_id_search;
-- Update Row for Friendships
UPDATE Friendships SET From_Account_id = :friendships_From_Friend_id WHERE From_Friend_id;
