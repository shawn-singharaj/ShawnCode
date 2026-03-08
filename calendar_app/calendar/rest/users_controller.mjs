import express from 'express';
import user from './users_model.mjs';
import asyncHandler from 'express-async-handler';

const router = express.Router();

// log in
router.post("/login", asyncHandler(async (req, res) => {
  const {email, password} = req.body;

  const User = await user.findEmail({email});

  if (User && User.password == password) { 
    res.status(200).json({success: true, userId: User._id});
  } else {
    res.status(401).json({message: "Incorrect Email or Password"});
  }
}));

// create account
router.post("/users", asyncHandler(async (req, res) => {
    const {email, password} = req.body;

    // required parameters
    if(!email || !password){
        return res.status(400).json({message: "Error: Incomplete Request"})
    }

    // create event
    const User = await user.createUser(email, password);
    res.status(201).json(User);
}));

router.get("/users", asyncHandler(async (req, res) => {
    const Users = await user.findUsers();

    res.status(200).json(Users);
}));

router.get("/users/:id", asyncHandler(async(req, res) => {
    const _id = req.params.id;

    if(_id){
        const User = await user.findEventById(_id);
        if(User){
            res.status(200).json(User);
        }
        else{
            res.status(404).json({message: "Error: User Not Found"});
        }
    }
}));

router.put("/users/:id", asyncHandler(async (req, res) => {
    const _id = req.params.id;
    const {email, password} = req.body;

    if(_id){
        const UpdatedUser = await user.updateUser(_id, email, password);
        if(UpdatedUser){
            res.status(200).json(UpdatedUser);
        }
        else{
            res.status(404).json({message: "Error: User Not Found"});
        }
    }
}));

router.delete("/users/:id", asyncHandler(async (req, res) => {
    const _id = req.params.id;
    const deleted = await user.deleteUser(_id);

    if(deleted.deletedCount == 1){
        res.status(204).json(deleted);
    }
    else{
        return res.status(404).json({message: "Error: User Not Found"});
    }
}));

export default router;