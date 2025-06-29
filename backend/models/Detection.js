
const mongoose = require('mongoose');

const DetectionSchema = new mongoose.Schema({
  distance: Number,
}, { timestamps: true });

module.exports = mongoose.model('Detection', DetectionSchema);
