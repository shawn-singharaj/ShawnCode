// Get the mongoose object
import mongoose, { mongo } from 'mongoose';
import 'dotenv/config';

let connection = undefined;
let StudySession = undefined;

/**
 * This function connects to the MongoDB server.
 */
async function connect(){
    try{ // specify the database and connect using .env link to database
        await mongoose.connect(process.env.MONGODB_CONNECT_STRING, {
            dbName: 'studysession_db'
        });
        connection = mongoose.connection;
        // construct the study session object
        StudySession = createModel();
        console.log("Successfully connected to MongoDB using Mongoose!");
    } catch(err){
        console.log(err);
        throw Error(`Could not connect to MongoDB ${err.message}`)
    }
}

function createModel(){
    // define schema
    const studysessionSchema = mongoose.Schema({
        name: {type: String, required: true},
        full_dur: {type: Number, required: true},
        num_breaks: {type: Number, required: true},
        break_dur: {type: Number, required: true},
        long_break_dur: {type: Number, required: true},
        study_dur: {type: Number, required: true},
        study_link: {type: String, required: true},
        break_link: {type: String, required: true},
    });
    // compile the model
    return mongoose.model("StudySession", studysessionSchema);
}

// create a study session object that will be saved in the database
async function createStudySession(name, full_dur, num_breaks, break_dur, long_break_dur, study_dur,
    study_link, break_link){
        
        const studysession = new StudySession({name : name, full_dur : full_dur, num_breaks : num_breaks, break_dur : break_dur, 
            long_break_dur : long_break_dur, study_dur : study_dur, study_link: study_link, break_link : break_link});
    return studysession.save();
}

// find a study session by filters
const findStudySession = async (filter) => {

    const query = StudySession.find(filter);
    return query.exec();
}

// find a study session by its unique id
const findStudySessionById = async (_id) => {

    try{
        const studysession = await StudySession.findById(_id);
        return studysession;
    }
    catch(err){
        throw err;
    }
}

// update the study session
async function updateStudySession(_id, name, full_dur, num_breaks, break_dur, long_break_dur, study_dur,
    study_link, break_link){

        const updated = await StudySession.findByIdAndUpdate(
            _id,
            { name, full_dur, num_breaks, break_dur, long_break_dur, study_dur, study_link, break_link },
            { new: true }
        );
        return updated;
};

// delete one study session by id
async function deleteStudySessionById(_id){

    try{
        const deleted = await StudySession.deleteOne({ _id });
        return deleted;
    }
    catch(err){
        throw err;
    }
};

export { connect, createStudySession, findStudySession, findStudySessionById, updateStudySession, deleteStudySessionById };
