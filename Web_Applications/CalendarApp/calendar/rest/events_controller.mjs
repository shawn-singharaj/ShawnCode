import express from 'express';
import asyncHandler from 'express-async-handler';
import * as events from './events_model.mjs';
import mongoose from 'mongoose';


const router = express.Router();

// create event
router.post("/", asyncHandler(async (req, res) => {
    const {date, type, title, description, time_end, reoccuring_day, userId} = req.body;

    // required parameters
    if(!date || !title || !userId){
        return res.status(400).json({message: "Error: Incomplete Request"})
    }

    // create event
    const Event = await events.createEvent(date, type, title, description, time_end, reoccuring_day, userId);
    res.status(201).json(Event);
}));

// get all events
router.get("/", asyncHandler(async (req, res) =>{
    const userId = req.query.userId;
    const filter = userId ? { userId } : {};    
    const all_Events = await events.findEvent(filter);

    res.status(200).json(all_Events);
}));

// get certain event
router.get("/:id", asyncHandler(async(req, res) => {
    const _id = req.params.id;

    if(_id){
        const Event = await events.findEventById(_id);
        if(Event){
            res.status(200).json(Event);
        }
        else{
            res.status(404).json({message: "Error: Not Found"});
        }
    }
}));

// Get events by userId
router.get('/user/:userId', asyncHandler(async (req, res) => {
  const { userId } = req.params;
  const {date} = req.query;

  let filter = {userId};


  if (date) {
    const startDate = new Date(date);
    const endDate = new Date(date);
    endDate.setDate(endDate.getDate() + 1);

    filter.date = { $gte: startDate, $lt: endDate };
  }

  const userevents = await events.findEvent(filter); 
  res.status(200).json(userevents);
}));

// update event by id
router.put("/:id", asyncHandler(async (req, res) => {
    const _id = req.params.id;
    const {date, type, title, description, time_end, reoccuring_day, userId} = req.body;

     // required parameters
    if(!date || !title){
        return res.status(400).json({message: "Error: Incomplete Request"})
    }

    if(_id){
        const UpdatedEvent = await events.updateEvent(_id, date, type, title, description, time_end, reoccuring_day, userId);
        if(UpdatedEvent){
            res.status(200).json(UpdatedEvent);
        }
        else{
            res.status(404).json({message: "Error: Not Found"});
        }
    }
}));

// delete event
router.delete("/:id", asyncHandler(async (req, res) => {
    const _id = req.params.id;
    const deleted = await events.deleteEventById(_id);


    if(deleted.deletedCount == 1){
        res.status(204).json(deleted);
    }
    else{
        return res.status(404).json({message: "Error: Not Found"});
    }
}));

export default router;