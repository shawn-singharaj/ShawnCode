// Get the mongoose object
import mongoose from 'mongoose';
import 'dotenv/config';

let connection = undefined;
let Exercises = undefined;

/**
 * This function connects to the MongoDB server.
 */
async function connect(){
    try{
        await mongoose.connect(process.env.MONGODB_CONNECT_STRING);
        connection = mongoose.connection;
        console.log("Successfully connected to MongoDB using Mongoose!");
        Exercises = createModel();
    } catch(err){
        console.log(err);
        throw Error(`Could not connect to MongoDB ${err.message}`)
    }
}

function createModel(){
    const exercisesSchema = mongoose.Schema({
        name: {type: String, required: true},
        reps: {type: Number, required: true},
        weight: {type: Number, required: true},
        unit: {type: String, required: true},
        date:{type: String, required: true},
    });
    return mongoose.model('exercises', exercisesSchema);
}

async function createExercise(name, reps, weight, unit, date){
    const exercise = new Exercises({name: name, reps: reps, weight: weight, unit: unit, date: date});
    return exercise.save();
}

const findExercises = async (filter) => {
    const query = Exercises.find(filter);
    return query.exec();
};

const findExercisesById = async (_id) => {
    try{
        const exercise = await Exercises.findById(_id);
        return exercise;
    }catch(err){
        throw err;
    }
};

async function updateExercise(_id, name, reps, weight, unit, date){
    
    const result = await Exercises.findByIdAndUpdate(
        _id, 
        { name, reps, weight, unit, date }, 
        { new: true } 
    );
    return result;
};

async function deleteExerciseById(_id) {
    
    try {
        const result = await Exercises.deleteOne({ _id });

        return result;
    } catch (err) {
        throw err;
    }
}


export { connect, createExercise, findExercises, findExercisesById, updateExercise, deleteExerciseById };
