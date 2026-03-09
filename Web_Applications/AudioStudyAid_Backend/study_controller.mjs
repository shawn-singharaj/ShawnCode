import 'dotenv/config';
import express from 'express';
import asyncHandler from 'express-async-handler';
import * as study from './study_model.mjs';

const app = express();
app.use(express.json())

const PORT = process.env.PORT;

app.listen(PORT, async () => {
    await study.connect(false)
    console.log(`Server listening on port ${PORT}...`);
});

// change endpoints here
// create study session 
app.post("/studysessions", asyncHandler(async (req, res) => {
    const {name, full_dur, num_breaks, break_dur, long_break_dur, study_dur, study_link, break_link} = req.body;

    // if one of the parameters are missing
    if(!name || !full_dur || !num_breaks || !break_dur || !long_break_dur || !study_dur || !study_link || !break_link){
        return res.status(400).json("Error: Invalid/Incomplete Request");
    }

    // if invalid parameters
    else if(name.length < 1 || full_dur < 1 || num_breaks < 0 || break_dur < 0 || long_break_dur < 0 || study_dur < 0){
        return res.status(400).json("Error Invalid Request Parameters");
    }

    // successful post
    const StudySession = await study.createStudySession(name, full_dur, num_breaks, break_dur, long_break_dur, study_dur, study_link, break_link);
    res.status(201).json(StudySession);

}));

// get study session
app.get("/studysessions", asyncHandler(async (req, res) => {

    const all_StudySessions = await study.findStudySession();

    res.status(200).json(all_StudySessions);

}));

// retreive one session by its unique id
app.get("/studysessions/:id", asyncHandler(async (req, res) => {
    const _id = req.params.id;

    if(_id){
        const StudySession = await study.findStudySessionById(_id);
        if(StudySession){
            res.status(200).json(StudySession);
        }
        else{
            res.status(404).json("Error: Not Found");
        }
    }
}));

// update one session by id
app.put("/studysessions/:id", asyncHandler(async (req, res) => {
    const _id = req.params.id;
    const { name, full_dur, num_breaks, break_dur, long_break_dur, study_dur, study_link, break_link } = req.body;

    // if one of the parameters are missing
    if(!name || !full_dur || !num_breaks || !break_dur || !long_break_dur || !study_dur || !study_link || !break_link){
        return res.status(400).json("Error: Invalid/Incomplete Request");
    }

    // if invalid parameters
    else if(name.length < 1 || full_dur < 1 || num_breaks < 0 || break_dur < 0 || long_break_dur < 0 || study_dur < 0){
        return res.status(400).json("Error Invalid Request Parameters");
    }

    if(_id){
        const UpdatedStudySession = await study.updateStudySession(_id, name, full_dur, num_breaks, break_dur, long_break_dur, study_dur, study_link, break_link);
        if(UpdatedStudySession){
            res.status(200).json(UpdatedStudySession);
        }
        else{
            res.status(404).json("Error: Not Found");
        }
    }
}));

// delete by id
app.delete("/studysessions/:id", asyncHandler(async (req, res) => {
    const _id = req.params.id;
    const deleted = await study.deleteStudySessionById(_id);

    if (deleted.deletedCount == 1) {
            return res.status(204).json(deleted);  
        } else {
            return res.status(404).json({message: "Error: Not found"});  
        }
}));
