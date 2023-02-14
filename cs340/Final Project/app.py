from flask import Flask, render_template
from flask import request, redirect
from db_connector import connect_to_database, execute_query
#create the web application
webapp = Flask(__name__)

#provide a route where requests on the web application can be addressed
@webapp.route('/hello')
#provide a view (fancy name for a function) which responds to any requests on this route
def hello():
    return "Hello World!"

#---------------------------------INDEX---------------------------------
@webapp.route('/index')
def load_index():
    return render_template('index.html')

#---------------------------------MEMBERSHIPS---------------------------------
# Load memberships page (select)
@webapp.route('/memberships')
def load_memberships():
    print("Fetching and rendering Memberships web page")
    db_connection = connect_to_database()
    query = "SELECT Account_id, Group_id FROM Memberships;"
    result = execute_query(db_connection, query).fetchall()
    return render_template('memberships.html', memberships=result)

# Search/filter membership page (select)
@webapp.route('/search_memberships', methods=['GET'])
def search_memberships():
    if request.method == 'GET':
        print("Searching membership web page")
        db_connection = connect_to_database()

        query = "SELECT * FROM Memberships WHERE "
        numVals = 0

        Account_id = request.args.get('search_Account_id')
        print(Account_id)
        if Account_id != "":
            query += "Account_id = " + str(Account_id)
            numVals += 1

        Group_id = request.args.get('search_Group_id')
        print(Group_id)
        if Group_id != "":
            if numVals > 0:
                query += " AND "
            query += "Group_id = \"" + str(Group_id) + "\""
            numVals += 1
        query += ";"

        if Account_id == "" and Group_id == "":
            return redirect('/memberships')
        
        print(query)
        result = execute_query(db_connection, query).fetchall()
        print(result)
        return render_template('memberships.html', memberships=result)

# Add membership (insert)
@webapp.route('/add_memberships', methods=['POST','GET'])
def add_memberships():
    if request.method == 'GET':
        load_memberships()
        return redirect('/memberships')
    elif request.method == 'POST':
        db_connection = connect_to_database()
        Account_id = request.form.get('add_Account_id')
        Group_id = request.form.get('add_Group_id')

        query = 'INSERT INTO Memberships (Account_id, Group_id) VALUES (%s,%s)'
        data = (Account_id, Group_id)
        if Account_id != "" and Group_id != "":
            execute_query(db_connection, query, data)
        return redirect('/memberships')

# Delete membership
@webapp.route('/delete_memberships')
def delete_memberships():
    db_connection = connect_to_database()

    del_query = "DELETE FROM Memberships WHERE "
    query_cond = ""
    numVals = 0

    Account_id = request.args.get('search_Account_id')
    Group_id = request.args.get('search_Group_id')

    if Account_id != "":
        query_cond += "Account_id = " + str(Account_id)
        numVals += 1

    if Group_id != "":
        if numVals > 0:
            query_cond += " AND "
        query_cond += "Group_id = " + str(Group_id)


    del_query += query_cond + ";"
    result = execute_query(db_connection, del_query).fetchall()
    return redirect('/memberships')

#---------------------------------FRIENDSHIPS---------------------------------
@webapp.route('/friendships')
def load_friendships():
    print("Fetching and rendering Friendships web page")
    db_connection = connect_to_database()
    query = "SELECT From_Account_id, To_Account_id FROM Friendships;"
    result = execute_query(db_connection, query).fetchall()
    print(result)
    return render_template('friendships.html', friendships=result)
    
# Search/filter friendships page (select)
@webapp.route('/search_friendships', methods=['GET'])
def search_friendships():
    if request.method == 'GET':
        print("Searching friendships web page")
        db_connection = connect_to_database()

        query = "SELECT * FROM Friendships WHERE "
        numVals = 0

        From_Account_id = request.args.get('search_From_Account_id')
        print(From_Account_id)
        if From_Account_id != "":
            query += "From_Account_id = " + str(From_Account_id)
            numVals += 1

        To_Account_id = request.args.get('search_To_Account_id')
        print(To_Account_id)
        if To_Account_id != "":
            if numVals > 0:
                query += " AND "
            query += "To_Account_id = \"" + str(To_Account_id) + "\""
            numVals += 1
        query += ";"

        if From_Account_id == "" and To_Account_id == "":
            return redirect('/friendships')
        
        print(query)
        result = execute_query(db_connection, query).fetchall()
        print(result)
        return render_template('friendships.html', friendships=result)

# Add friendships (insert)
@webapp.route('/add_friendships', methods=['POST','GET'])
def add_friendships():
    if request.method == 'GET':
        return redirect('/friendships')
    elif request.method == 'POST':
        db_connection = connect_to_database()
        print("Add new friendships!")
        From_Account_id = request.form.get('add_From_Account_id')
        To_Account_id = request.form.get('add_To_Account_id')

        query = 'INSERT INTO Friendships (From_Account_id, To_Account_id) VALUES (%s,%s)'
        data = (From_Account_id, To_Account_id)
        if From_Account_id != "" and To_Account_id != "":
            execute_query(db_connection, query, data)
        return redirect('/friendships')

# Delete friendships
@webapp.route('/delete_friendships')
def delete_friendships():
    db_connection = connect_to_database()
    From_Account_id = request.args.get('search_From_Account_id')
    To_Account_id = request.args.get('search_To_Account_id')
    if From_Account_id == "" or To_Account_id == "":
        return redirect('/friendships')
        
    query = "DELETE FROM Friendships WHERE From_Account_id = " + str(From_Account_id) + " AND To_Account_id = " + str(To_Account_id) + ";"

    result = execute_query(db_connection, query).fetchall()
    return redirect('/friendships')

# -------------------------------ACCOUNTS--------------------------------

# Load account page (select)
@webapp.route('/accounts')
def load_accounts():
    print("Fetching and rendering Account web page")
    db_connection = connect_to_database()
    query = "SELECT Account_id, Username, Email FROM Accounts;"
    result = execute_query(db_connection, query).fetchall()
    print(result)
    return render_template('accounts.html', accounts=result)

# Search/filter account page (select)
@webapp.route('/search_account', methods=['GET'])
def search_accounts():
    if request.method == 'GET':
        print("Searching account web page")
        db_connection = connect_to_database()

        query = "SELECT * FROM Accounts WHERE "
        numVals = 0

        Account_id = request.args.get('search_Account_id')
        print(Account_id)
        if Account_id != "":
            query += "Account_id = " + str(Account_id)
            numVals += 1

        Username = request.args.get('search_Username')
        print(Username)
        if Username != "":
            if numVals > 0:
                query += " AND "
            query += "Username = \"" + str(Username) + "\""
            numVals += 1
        
        Email = request.args.get('search_Email')
        print(Email)
        if Email != "":
            if numVals > 0:
                query += " AND "
            query += "Email = \"" + str(Email) + "\""
        query += ";"

        if Account_id == "" and Username == "" and Email == "":
            return redirect('/accounts')
        
        print(query)
        result = execute_query(db_connection, query).fetchall()
        print(result)
        return render_template('accounts.html', accounts=result)
    

# Add account (insert)
@webapp.route('/add_account', methods=['POST','GET'])
def add_accounts():
    if request.method == 'GET':
        load_accounts()
        return redirect('/accounts')
    elif request.method == 'POST':
        db_connection = connect_to_database()
        print("Add new people!")
        # Account_id = request.form['add_Account_id']
        Username = request.form.get('add_Username')
        Email = request.form.get('add_Email')

        query = 'INSERT INTO Accounts (Username, Email) VALUES (%s,%s)'
        data = (Username, Email)
        if Username != "" and Email != "":
            execute_query(db_connection, query, data)
        return redirect('/accounts')

# Delete account
@webapp.route('/delete_account')
def delete_account():
    db_connection = connect_to_database()

    del_query = "DELETE FROM Accounts WHERE "
    query_cond = ""
    numVals = 0

    Account_id = request.args.get('search_Account_id')
    Username = request.args.get('search_Username')
    Email = request.args.get('search_Email')

    if Account_id != "":
        query_cond += "Account_id = " + str(Account_id)
        numVals += 1
    
    if Username != "":
        if numVals > 0:
            query_cond += " AND "
        query_cond += "Username = \"" + str(Username)+ "\""
        numVals += 1
    
    if Email != "":
        if numVals > 0:
            query_cond += " AND "
        query_cond += "Email = \"" + str(Email)+ "\""
        
    del_query += query_cond + ";"
    if Account_id != "" or Username != "" or Email != "":
        result = execute_query(db_connection, del_query).fetchall()

    return redirect('/accounts')

# Update account
@webapp.route('/update_account', methods=['POST','GET'])
def update_accounts():
    if request.method == 'POST':
        print("Updating account web page")
        db_connection = connect_to_database()

        query = "UPDATE Accounts SET "
        numVals = 0

        Username = request.form.get('search_Username')
        if Username != "":
            query += "Username = \"" + str(Username) + "\""
            numVals += 1
        
        Email = request.form.get('search_Email')
        if Email != "":
            if numVals > 0:
                query += ", "
            query += "Email = \"" + str(Email) + "\""

        Account_id = request.form.get('search_Account_id')

        query += " WHERE Account_id = " + str(Account_id) + ";"

        if Account_id == "" or (Username == "" and Email == ""):
            return redirect('/accounts')
        
        print(query)
        result = execute_query(db_connection, query).fetchall()
        return redirect('/accounts')
    elif request.method == 'GET':
        return redirect('/accounts')

        
# -------------------------------COMMENTS--------------------------------
# Load comments page (select)
@webapp.route('/comments')
def load_comments():
    print("Fetching and rendering Comments web page")
    db_connection = connect_to_database()
    query = "SELECT Comment_id, Text, Account_id, Post_id FROM Comments;"
    result = execute_query(db_connection, query).fetchall()
    print(result)
    return render_template('comments.html', comments=result)

# Search/filter comments page (select)
@webapp.route('/search_comments', methods=['GET'])
def search_comments():
    if request.method == 'GET':
        print("Searching comments web page")
        db_connection = connect_to_database()

        query = "SELECT * FROM Comments WHERE "
        numVals = 0

        Comment_id = request.args.get('search_Comment_id')
        if Comment_id != "":
            query += "Comment_id = " + str(Comment_id)
            numVals += 1
        
        Text = request.args.get('search_Text')
        if Text != "":
            if numVals > 0:
                query += " AND "
            query += "Text = \"" + str(Text) + "\""
            numVals += 1

        Account_id = request.args.get('search_Account_id')
        if Account_id != "":
            if numVals > 0:
                query += " AND "
            query += "Account_id = " + str(Account_id)
            numVals += 1

        Post_id = request.args.get('search_Post_id')
        if Post_id != "":
            if numVals > 0:
                query += " AND "
            query += "Post_id = " + str(Post_id)
            numVals += 1

        query += ";"

        if Account_id == "" and Comment_id == "" and Text == "" and Post_id == "":
            return redirect('/comments')
        
        print(query)
        result = execute_query(db_connection, query).fetchall()
        print(result)
        return render_template('comments.html', comments=result)
    

# Add comment (insert)
@webapp.route('/add_comments', methods=['POST','GET'])
def add_comments():
    if request.method == 'GET':
        load_comments()
        return redirect('/comments')
    elif request.method == 'POST':
        db_connection = connect_to_database()
        print("Add new comments")
        #Comment_id = request.form['add_Comment_id']
        Text = request.form['add_Text']
        Account_id = request.form['add_Account_id']
        Post_id = request.form['add_Post_id']

        query = 'INSERT INTO Comments (Text, Account_id, Post_id) VALUES (%s,%s,%s)'
        data = (Text, Account_id, Post_id)
        if Text != "" and Account_id != "" and Post_id != "":
            execute_query(db_connection, query, data)
        return redirect('/comments')

# Delete comment
@webapp.route('/delete_comments')
def delete_comments():
    db_connection = connect_to_database()

    del_query = "DELETE FROM Comments WHERE "
    query_cond = ""
    numVals = 0
    
    Comment_id = request.args.get('search_Comment_id')
    Post_id = request.args.get('search_Post_id')
    Text = request.args.get('search_Text')
    Account_id = request.args.get('search_Account_id')
    
    if Comment_id != "":
        query_cond += "Comment_id = " + str(Comment_id)
        numVals += 1

    if Post_id != "":
        if numVals > 0:
            query_cond += " AND "
        query_cond += "Post_id = " + str(Post_id)
        numVals += 1
    
    if Text != "":
        if numVals > 0:
            query_cond += " AND "
        query_cond += "Text = \"" + str(Text) + "\""
        numVals += 1
    
    if Account_id != "":
        if numVals > 0:
            query_cond += " AND "
        query_cond += "Account_id = " + str(Account_id)
        numVals += 1

    del_query += query_cond + ";"
    if Comment_id != "" or Post_id != "" or Text != "" or Account_id != "":
        result = execute_query(db_connection, del_query).fetchall()
    return redirect('/comments')

# Update comment
@webapp.route('/update_comments', methods=['POST','GET'])
def update_comments():
    if request.method == 'POST':
        print("Updating comment web page")
        db_connection = connect_to_database()

        query = "UPDATE Comments SET "
        numVals = 0

        Comment_id = request.form.get('search_Comment_id')
        Account_id = request.form.get('search_Account_id')
        Text = request.form.get('search_Text')
        Post_id = request.form.get('search_Post_id')

        if Account_id != "":
            query += "Account_id = \"" + str(Account_id) + "\""
            numVals += 1
        
        if Text != "":
            if numVals > 0:
                query += ", "
            query += "Text = \"" + str(Text) + "\""

        if Post_id != "":
            if numVals > 0:
                query += ", "
            query += "Post_id = \"" + str(Post_id) + "\""
            
        query += " WHERE Comment_id = " + str(Comment_id) + ";"

        if Comment_id == "" or (Account_id == "" and Text == "" and Post_id == ""):
            return redirect('/comments')
        
        result = execute_query(db_connection, query).fetchall()
        return redirect('/comments')
    elif request.method == 'GET':
        return redirect('/comments')


# -------------------------------GROUPS--------------------------------
# Load groups page (select)
@webapp.route('/groups')
def load_group():
    print("Fetching and rendering Groups web page")
    db_connection = connect_to_database()
    query = "SELECT Group_id, Group_name FROM Groups;"
    result = execute_query(db_connection, query).fetchall()
    print(result)
    return render_template('groups.html', groups=result)

# Search/filter group page (select)
@webapp.route('/search_group', methods=['GET'])
def search_group():
    if request.method == 'GET':
        print("Searching group web page")
        db_connection = connect_to_database()

        query = "SELECT * FROM Groups WHERE "
        numVals = 0

        Group_id = request.args.get('search_Group_id')
        if Group_id != "":
            query += "Group_id = " + str(Group_id)
            numVals += 1

        Group_name = request.args.get('search_Group_name')
        if Group_name != "":
            if numVals > 0:
                query += " AND "
            query += "Group_name = \"" + str(Group_name) + "\""
            numVals += 1

        if Group_id == "" and Group_name == "":
            return redirect('/groups')
        
        print(query)
        result = execute_query(db_connection, query).fetchall()
        print(result)
        return render_template('groups.html', groups=result)
    

# Add group (insert)
@webapp.route('/add_group', methods=['POST','GET'])
def add_group():
    if request.method == 'GET':
        load_group()
        return redirect('/groups')
    elif request.method == 'POST':
        db_connection = connect_to_database()
        Group_name = request.form.get('add_Group_name')

        query = 'INSERT INTO Groups (Group_name) VALUES (\"' + Group_name + '\")'
        if Group_name != "":
            execute_query(db_connection, query)
        return redirect('/groups')

# Delete group
@webapp.route('/delete_group')
def delete_group():
    db_connection = connect_to_database()

    del_query = "DELETE FROM Groups WHERE "
    query_cond = ""
    numVals = 0

    Group_id = request.args.get('search_Group_id')
    Group_name = request.args.get('search_Group_name')

    if Group_id != "":
        query_cond += "Group_id = " + str(Group_id)
        numVals += 1

    if Group_name != "":
        if numVals > 0:
            query_cond += " AND "
        query_cond += "Group_name = \"" + Group_name + "\""

    del_query += query_cond + ";"
    # print("Group ID: (" + str(Group_id) + "), Group_name: (" + Group_name + ")")
    if Group_id != "" or Group_name != "":
        result = execute_query(db_connection, del_query).fetchall()
    return redirect('/groups')

# Update group
@webapp.route('/update_group', methods=['POST','GET'])
def update_groups():
    if request.method == 'POST':
        print("Updating group web page")
        db_connection = connect_to_database()

        query = "UPDATE Groups SET "
        numVals = 0

        Group_name = request.form.get('search_Group_name')
        # print(Group_name)
        if Group_name != "":
            query += "Group_name = \"" + str(Group_name) + "\""
            numVals += 1

        Group_id = request.form.get('search_Group_id')
        query += " WHERE Group_id = " + str(Group_id) + ";"

        if Group_id == "" or Group_name == "":
            return redirect('/groups')
        
        print(query)
        result = execute_query(db_connection, query).fetchall()
        return redirect('/groups')
    elif request.method == 'GET':
        return redirect('/groups')


# -------------------------------MESSAGES--------------------------------
# Load messages page (select)
@webapp.route('/messages')
def load_messages():
    print("Fetching and rendering Messages web page")
    db_connection = connect_to_database()
    query = "SELECT Message_id, Account_id, Group_id, Message FROM Messages;"
    result = execute_query(db_connection, query).fetchall()
    print(result)
    return render_template('messages.html', messages=result)

# Search/filter messages page (select)
@webapp.route('/search_messages', methods=['GET'])
def search_messages():
    if request.method == 'GET':
        print("Searching messages web page")
        db_connection = connect_to_database()

        query = "SELECT * FROM Messages WHERE "
        numVals = 0

        Message_id = request.args.get('search_Message_id')
        if Message_id != "":
            query += "Message_id = " + str(Message_id)
            numVals += 1

        Account_id = request.args.get('search_Account_id')
        if Account_id != "":
            if numVals > 0:
                query += " AND "
            query += "Account_id = " + str(Account_id)
            numVals += 1

        Group_id = request.args.get('search_Group_id')
        if Group_id != "":
            if numVals > 0:
                query += " AND "
            query += "Group_id = " + str(Group_id)
            numVals += 1
        
        Message = request.args.get('search_Message')
        if Message != "":
            if numVals > 0:
                query += " AND "
            query += "Message = \"" + str(Message) + "\""
            numVals += 1

        query += ";"

        if Message_id == "" and Account_id == "" and Message == "" and Group_id == "":
            return redirect('/messages')
        
        print(query)
        result = execute_query(db_connection, query).fetchall()
        print(result)
        return render_template('messages.html', messages=result)
    

# Add message (insert)
@webapp.route('/add_messages', methods=['POST','GET'])
def add_message():
    if request.method == 'GET':
        load_messages()
        return redirect('/messages')
    elif request.method == 'POST':
        db_connection = connect_to_database()
        print("Add new messages")
        # Message_id = request.form['add_Message_id']
        Message = request.form['add_Message']
        Account_id = request.form['add_Account_id']
        Group_id = request.form['add_Group_id']

        query = 'INSERT INTO Messages (Message, Account_id, Group_id) VALUES (%s,%s,%s)'
        data = (Message, Account_id, Group_id)

        if Message != "" and Account_id != "" and Group_id != "":
            execute_query(db_connection, query, data)
        return redirect('/messages')

# Delete message
@webapp.route('/delete_messages')
def delete_messages():
    db_connection = connect_to_database()

    del_query = "DELETE FROM Messages WHERE "
    query_cond = ""
    numVals = 0

    Message_id = request.args.get('search_Message_id')
    Account_id = request.args.get('search_Account_id')
    Group_id = request.args.get('search_Group_id')
    Message = request.args.get('search_Message')

    if Message_id != "":
        query_cond += "Message_id = " + str(Message_id)
        numVals += 1
    
    if Account_id != "":
        if numVals > 0:
            query_cond += " AND "
        query_cond += "Account_id = " + str(Account_id)
        numVals += 1
    
    if Group_id != "":
        if numVals > 0:
            query_cond += " AND "
        query_cond += "Group_id = " + str(Group_id)
        numVals += 1
    
    if Message != "":
        if numVals > 0:
            query_cond += " AND "
        query_cond += "Message = \"" + str(Message)+ "\""
        
    del_query += query_cond + ";"
    if Message_id != "" or Account_id != "" or Group_id != "" or Message != "":
        result = execute_query(db_connection, del_query).fetchall()
    return redirect('/messages')

# Update message
@webapp.route('/update_messages', methods=['POST','GET'])
def update_messages():
    if request.method == 'POST':
        print("Updating messages web page")
        db_connection = connect_to_database()

        query = "UPDATE Messages SET "
        numVals = 0

        Message_id = request.form.get('search_Message_id')
        Message = request.form.get('search_Message')
        Account_id = request.form.get('search_Account_id')
        Group_id = request.form.get('search_Group_id')

        if Message != "":
            query += "Message = \"" + str(Message) + "\""
            numVals += 1
        
        if Account_id != "":
            if numVals > 0:
                query += ", "
            query += "Account_id = " + str(Account_id)

        if Group_id != "":
            if numVals > 0:
                query += ", "
            query += "Group_id = " + str(Group_id)

        query += " WHERE Message_id = " + str(Message_id) + ";"

        if Message_id == "" or (Message == "" and Account_id == "" and Group_id == ""):
            return redirect('/messages')
        
        print(query)
        result = execute_query(db_connection, query).fetchall()
        return redirect('/messages')
    elif request.method == 'GET':
        return redirect('/messages')


# -------------------------------POSTS--------------------------------
# Load posts page (select)
@webapp.route('/posts')
def load_posts():
    print("Fetching and rendering Posts web page")
    db_connection = connect_to_database()
    query = "SELECT Post_id, Text, Account_id FROM Posts;"
    result = execute_query(db_connection, query).fetchall()
    print(result)
    return render_template('posts.html', posts=result)

# Search/filter posts page (select)
@webapp.route('/search_posts', methods=['GET'])
def search_posts():
    if request.method == 'GET':
        print("Searching posts web page")
        db_connection = connect_to_database()

        query = "SELECT * FROM Posts WHERE "
        numVals = 0

        Post_id = request.args.get('search_Post_id')
        print(Post_id)
        if Post_id != "":
            query += "Post_id = " + str(Post_id)
            numVals += 1

        Text = request.args.get('search_Text')
        print(Text)
        if Text != "":
            if numVals > 0:
                query += " AND "
            query += "Text = \"" + str(Text) + "\""
            numVals += 1

        Account_id = request.args.get('search_Account_id')
        print(Account_id)
        if Account_id != "":
            if numVals > 0:
                query += " AND "
            query += "Account_id = " + str(Account_id)
            numVals += 1

        if Post_id == "" and Text == "" and Account_id == "":
            return redirect('/posts')
        
        print(query)
        result = execute_query(db_connection, query).fetchall()
        print(result)
        return render_template('posts.html', posts=result)
    

# Add posts (insert)
@webapp.route('/add_posts', methods=['POST','GET'])
def add_posts():
    if request.method == 'GET':
        add_posts()
        return redirect('/posts')
    elif request.method == 'POST':
        db_connection = connect_to_database()
        print("Add new posts!")
        # Post_id = request.form['add_Post_id']
        Text = request.form['add_Text']
        Account_id = request.form['add_Account_id']

        query = 'INSERT INTO Posts (Text, Account_id) VALUES (%s,%s)'
        data = (Text, Account_id)
        if Text != "" and Account_id != "":
            execute_query(db_connection, query, data)
        return redirect('/posts')

# Delete posts
@webapp.route('/delete_posts')
def delete_posts():
    print("deleting post")
    db_connection = connect_to_database()

    del_query = "DELETE FROM Posts WHERE "
    query_cond = ""
    numVals = 0

    Post_id = request.args.get('search_Post_id')
    Text = request.args.get('search_Text')
    Account_id = request.args.get('search_Account_id')

    if Post_id != "":
        query_cond += "Post_id = " + str(Post_id)
        numVals += 1
    
    if Text != "":
        if numVals > 0:
            query_cond += " AND "
        query_cond += "Text = \"" + str(Text)+ "\""
        numVals += 1
    
    if Account_id != "":
        if numVals > 0:
            query_cond += " AND "
        query_cond += "Account_id = " + str(Account_id)
        

    del_query += query_cond + ";"
    if Post_id != "" or Text != "" or Account_id != "":
        result = execute_query(db_connection, del_query).fetchall()
    return redirect('/posts')

# Update posts
@webapp.route('/update_posts', methods=['POST','GET'])
def update_posts():
    if request.method == 'POST':
        print("Updating posts web page")
        db_connection = connect_to_database()

        query = "UPDATE Posts SET "
        numVals = 0
        
        Text = request.form.get('search_Text')
        # print(Text)
        if Text != "":
            query += "Text = \"" + str(Text) + "\""
            numVals += 1

        Account_id = request.form.get('search_Account_id')
        # print(Account_id)
        if Account_id != "":
            if numVals > 0:
                query += ", "
            query += "Account_id = \"" + str(Account_id) + "\""

        Post_id = request.form.get('search_Post_id')

        query += " WHERE Post_id = " + str(Post_id) + ";"

        if Post_id == "" or (Text == "" and Account_id == ""):
            return redirect('/posts')
        
        print(query)
        if Post_id != "":
            result = execute_query(db_connection, query).fetchall()
        return redirect('/posts')
    elif request.method == 'GET':
        return redirect('/posts')