import 'dotenv/config';
import express from 'express';
import asyncHandler from 'express-async-handler';
import * as users from './model.mjs';

const app = express();
app.use(express.json())

const PORT = process.env.PORT;

app.listen(PORT, async () => {
    await users.connect(false)
    console.log(`Server listening on port ${PORT}...`);
});

app.post("/users", asyncHandler(async (req, res) =>{
    const { name, age, email, phoneNumber } = req.body;

    if(!name || !age || !email){
        return res.status(400).send("You must enter a name, age, and email.");
    }

    const user = await users.createUser(name, age, email, phoneNumber);

    res.status(201).json(user);

}));

app.get("/users", asyncHandler(async (req, res) => {
    const { name, age, email, phoneNumber } = req.query;

    const all_users = await users.findUsers();


    if(!name && !age && !email && !phoneNumber){
        res.status(200).json(all_users);
    }   

    if(name){
        let found_user = null;
    for (let user of all_users) {
        if(user.name === name){
            found_user = user;
            break;
        }
    }
    res.status(200).json(found_user);
    }   
    else if(age){
     let found_user = null;
     for (let user of all_users) {
        if(user.age == age){
            found_user = user;
            break;
        }
        }
        res.status(200).json(found_user);
    }
    if(email){
        let found_user = null;
        for (let user of all_users) {
           if(user.email === email){
               found_user = user;
               break;
           }
           }
           res.status(200).json(found_user);
    }
    if(phoneNumber){
        let found_user = null;
        for (let user of all_users) {
           if(user.phoneNumber == phoneNumber){
               found_user = user;
               break;
           }
           }
           res.status(200).json(found_user);
    }
})); 

app.get("/users/:id", asyncHandler(async (req, res) => {
    const _id = req.params.id;
    
    if(_id){
      const userById = await users.findUsersById(_id);
      if(userById){
        return res.status(200).json(userById);
      }
      else{
        return res.status(404).json("User not found");
      }
    }
}));

app.put("/users/:id", asyncHandler(async (req, res) => {
    const user_id = req.params.id;
    const { name, age, email, phoneNumber } = req.body;

    const updatedUser = await users.updateUser(user_id, name, age, email, phoneNumber);

    if(updatedUser){
        res.status(200).json(updatedUser);
    }
    else{
        res.status(404).json("Error: Not found");
    }
}));

app.delete("/users/:id", asyncHandler(async (req, res) => {
    const user_id = req.params.id;
    const result = await users.deleteUserById(user_id);

    if (result.deletedCount == 1) {
            return res.status(204).json(result);  
        } else {
            return res.status(404).json({message: "Error: Not found"});  
        }

}));

app.delete("/users", asyncHandler(async (req, res) => {
    const { name, age, email, phoneNumber } = req.query;

    const filter = {};

    if (name) filter.name = name;
    if (age) filter.age = age;
    if (email) filter.email = email;
    if (phoneNumber) filter.phoneNumber = phoneNumber;

    const result = await users.deleteUser(filter);

    if (result.deletedCount == 1) {
        return res.status(200).json({message: "deletedCount: " + result.deletedCount}); 
    } else {
        return res.status(404).json({message: "Error: not found"});  
    }

}));