// Get the mongoose object
import mongoose from 'mongoose';
import { ObjectId } from "mongodb";


    // define schema
const eventSchema = mongoose.Schema({
    date: {type: Date, required: true},
    type: {type: String, required: false},
    title: {type: String, required: true},
    description: {type: String, required: false},
    time_end: {type: Date, required: false},
    reoccuring_day: {type: String, required: false},
    userId: { type: mongoose.Schema.Types.ObjectId, ref: 'User', required: true }
    });
    // compile and return model
const Event =  mongoose.model("Event", eventSchema);


// create an event for database
async function createEvent(date, type, title, description, time_end, reoccuring_day, userId){
    // create the new event object
    const event = new Event({date : date, type : type, title : title, description : description, time_end: time_end, reoccuring_day: reoccuring_day, userId : userId});

    return event.save();
;}

// find a event by filters
const findEvent = async (filter) => {

    const query = Event.find(filter);
    return query.exec();
};

// find a event by its unique id
const findEventById = async (_id) => {

    try{ // find by id and return
        const event = await Event.findById(_id);
        return event;
    }
    catch(err){
        throw err;
    }
};

// update the event
async function updateEvent(_id, date, type, title, description, time_end, reoccuring_day, userId){
        // update by id
        const updated = await Event.findByIdAndUpdate(
            _id,
            {date, type, title, description, time_end, reoccuring_day, userId},
            {new: true}
        );
        return updated;
};

// delete one event by id
async function deleteEventById(_id){
    try{ 
        const deleted = await Event.deleteOne({_id});
        return deleted;
    }
    catch(err){
        throw err;
    }
};

export {Event, createEvent, findEvent, findEventById, updateEvent, deleteEventById};
