"use strict";

const gulp = require('gulp');
const javascriptObfuscator = require('gulp-javascript-obfuscator');
// const del = require("del");

gulp.task("build", () => {
  return gulp.src('./src/main.js')
    .pipe(javascriptObfuscator({
      compact: true
    }))
    .pipe(gulp.dest('./build/js'));
});
