import mongoose from 'mongoose';

// define user
const userSchema = new mongoose.Schema({
  email: {type: String, required: true, unique: true},
  password: {type: String, required: true} 
});

const User = mongoose.model('User', userSchema);

async function createUser(email, password){
    const user = new User({email : email, password : password})
    return user.save();
};

const findUsers = async (filter) => {
    const query = User.find(filter);
    return query.exec();
};

const findUserById = async (_id) => {

    try{ // find by id and return
        const user = await User.findById(_id);
        return user;
    }
    catch(err){
        throw err;
    }
};

async function updateUser(_id, email, password){
    const updated = await User.findByIdAndUpdate(
        _id,
        {email, password},
        {new : true}
    );
    return updated;
}

async function deleteUser(_id){
    try{
        const deleted = await User.deleteOne({_id});
        return deleted;
    }
    catch(err){
        throw err;
    }
};

async function findEmail({email}){
    return User.findOne({email});
}

export default {User, createUser, findUsers, findUserById, updateUser, deleteUser, findEmail};