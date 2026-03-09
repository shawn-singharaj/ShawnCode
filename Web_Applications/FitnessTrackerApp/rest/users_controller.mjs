import 'dotenv/config';
import express, { response } from 'express';
import asyncHandler from 'express-async-handler';
import * as exercises from './users_model.mjs';

const app = express();
app.use(express.json())

const PORT = process.env.PORT;

app.listen(PORT, async () => {
    await exercises.connect(false)
    console.log(`Server listening on port ${PORT}...`);
});

function isDateValid(date){
    const format = /^\d\d-\d\d-\d\d$/;
    return format.test(date);
};

// post
app.post("/exercises", asyncHandler(async (req, res) => {
    const {name, reps, weight, unit, date} = req.body;

    if(!name || !reps || !weight || !unit || !date){
        return res.status(400).json("Error: Invalid request");
    }

    else if(name.length < 1 || reps < 0 || typeof(reps) != "number" || weight < 0 || (unit != "kgs" && unit != "lbs")
    || !isDateValid(date)){
        return res.status(400).json("Error: Invalid request");
    }

    const exercise = await exercises.createExercise(name, reps, weight, unit, date);

    res.status(201).json(exercise);

}));

// get 
app.get("/exercises", asyncHandler(async (req, res) => {

    const all_exercises = await exercises.findExercises();

    res.status(200).json(all_exercises);

})); 

// get by id
app.get("/exercises/:id", asyncHandler(async (req, res) => {
    const _id = req.params.id;
    
    if(_id){
      const ExerciseById = await exercises.findExercisesById(_id);
      if(ExerciseById){
        return res.status(200).json(ExerciseById);
      }
      else{
        return res.status(404).json("Error: Not found");
      }
    }
}));

// put/update
app.put("/exercises/:id", asyncHandler(async (req, res) => {
    const exercise_id = req.params.id;
    const { name, reps, weight, unit, date } = req.body;

    if(!name || !reps || !weight || !unit || !date){
        return res.status(400).json("Error: Invalid request");
    }

    else if(name.length < 1 || reps < 0 || weight < 0 || (unit != "kg" && unit != "lbs")
    || !isDateValid(date)){
        return res.status(400).json("Error: Invalid request");
    }

    const updatedExercise = await exercises.updateExercise(exercise_id, name, reps, weight, unit, date);

    if(updatedExercise){
        res.status(200).json(updatedExercise);
    }
    else{
        res.status(404).json("Error: Not found");
    }
}));

// delete by id
app.delete("/exercises/:id", asyncHandler(async (req, res) => {
    const exercise_id = req.params.id;
    const result = await exercises.deleteExerciseById(exercise_id);

    if (result.deletedCount == 1) {
            return res.status(204).json(result);  
        } else {
            return res.status(404).json({message: "Error: Not found"});  
        }

}));
