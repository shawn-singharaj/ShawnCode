import express from 'express';
import mongoose from 'mongoose';
import dotenv from 'dotenv';
import eventRoutes from './events_controller.mjs';
import userRoutes from './users_controller.mjs';
import cors from 'cors';

dotenv.config();

const app = express();
app.use(cors());
app.use(express.json());

await mongoose.connect(process.env.MONGODB_CONNECT_STRING, {
  dbName: 'events_db'
});
console.log("Successfully connected to MongoDB using Mongoose!");

// Register routes
app.use('/events', eventRoutes);
app.use('/', userRoutes);

const PORT = process.env.PORT || 3000;
app.listen(PORT, () => console.log(`Server listening on port ${PORT}...`));