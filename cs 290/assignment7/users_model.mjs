// Get the mongoose object
import mongoose from 'mongoose';
import 'dotenv/config';

let connection = undefined;
let Users = undefined

/**
 * This function connects to the MongoDB server.
 */
async function connect(){
    try{
        await mongoose.connect(process.env.MONGODB_CONNECT_STRING);
        connection = mongoose.connection;
        console.log("Successfully connected to MongoDB using Mongoose!");
        Users = createModel();
    } catch(err){
        console.log(err);
        throw Error(`Could not connect to MongoDB ${err.message}`)
    }
}

function createModel(){
    const usersSchema = mongoose.Schema({
        name: {type: String, required: true},
        age: {type: Number, required: true},
        email: {type: String, required: true},
        phoneNumber: {type: Number, required: false},
    });
    return mongoose.model('users', usersSchema);
}

async function createUser(name, age, email, phoneNumber){
    const users = new Users({name: name, age: age, email: email, phoneNumber: phoneNumber});
    return users.save();
}

const findUsers = async (filter) => {
    const query = Users.find(filter);
    return query.exec();
};

const findUsersById = async (_id) => {
    try{
        const user = await Users.findById(_id);
        return user;
    }catch(err){
        throw err;
    }
};

async function updateUser(_id, name, age, email, phoneNumber){
    // const result = await Users.findBy({_id: _id}, 
    //     {name: name, age: age, email: email, phoneNumber: phoneNumber});
    const result = await Users.findByIdAndUpdate(
        _id, 
        { name, age, email, phoneNumber }, 
        { new: true } 
    );
    return result;
}

async function deleteUserById(_id) {
    
    try {
        const result = await Users.deleteOne({ _id });

        return result;
    } catch (err) {
        throw err;
    }
}

async function deleteUser(filter) {
    try {
        const result = await Users.deleteOne(filter);

        return result;
    } catch (err) {
        throw err;
    }
}

export { connect, createUser, findUsers, findUsersById, updateUser, deleteUserById, deleteUser };
