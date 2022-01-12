`use strict`;

const calculator = (mathProblemArr) => {
  const operations = {
    multiplication: `*`,
    division: `/`,
    addition: `+`,
    subtraction: `-`,
  }
  const brackets = {
    open: `(`,
    close: `)`,
  }
  while (mathProblemArr.includes(brackets.open)) {
    let openCount = 0;
    let closeIndex = -1;
    let openIndex = mathProblemArr.indexOf(brackets.open);
    for (let i = 0; i < mathProblemArr.length; i++) {
      if (mathProblemArr[i] === brackets.open) {
        openCount++;
        continue;
      }
      if (mathProblemArr[i] === brackets.close) {
        openCount--;
        if (openCount === 0) {
          closeIndex = i;
          break;
        }
      }
    }
    mathProblemArr = [...mathProblemArr.slice(0, openIndex), ...calculator(mathProblemArr.slice(openIndex+1, closeIndex)), ...mathProblemArr.slice(closeIndex+1)];
  }
  if (!mathProblemArr.includes(brackets.open)) {
    while (mathProblemArr.length > 1) {
      while (mathProblemArr.includes(operations.multiplication) || mathProblemArr.includes(operations.division)) {
        let multiplicationSymbolIndex = mathProblemArr.indexOf(operations.multiplication);
        let divisionSymbolIndex = mathProblemArr.indexOf(operations.division);
        if ((divisionSymbolIndex === -1 || multiplicationSymbolIndex <= divisionSymbolIndex) && multiplicationSymbolIndex !== -1) {
          mathProblemArr = [...mathProblemArr.slice(0, multiplicationSymbolIndex-1), mathProblemArr[multiplicationSymbolIndex-1] * mathProblemArr[multiplicationSymbolIndex+1], ...mathProblemArr.slice(multiplicationSymbolIndex+2)];
        } else {
          mathProblemArr = [...mathProblemArr.slice(0, divisionSymbolIndex-1), mathProblemArr[divisionSymbolIndex-1] / mathProblemArr[divisionSymbolIndex+1], ...mathProblemArr.slice(divisionSymbolIndex+2)];
        }
      }
      while (mathProblemArr.includes(operations.addition) || mathProblemArr.includes(operations.subtraction)) {
        let additionSymbolIndex = mathProblemArr.indexOf(operations.addition);
        let subtractionSymbolIndex = mathProblemArr.indexOf(operations.subtraction);
        if ((subtractionSymbolIndex === -1 || additionSymbolIndex <= subtractionSymbolIndex) && additionSymbolIndex !== -1) {
          mathProblemArr = [...mathProblemArr.slice(0, additionSymbolIndex-1), mathProblemArr[additionSymbolIndex-1] + mathProblemArr[additionSymbolIndex+1], ...mathProblemArr.slice(additionSymbolIndex+2)];
        } else {
          mathProblemArr = [...mathProblemArr.slice(0, subtractionSymbolIndex-1), mathProblemArr[subtractionSymbolIndex-1] - mathProblemArr[subtractionSymbolIndex+1], ...mathProblemArr.slice(subtractionSymbolIndex+2)];
        }
      }
    }
    return mathProblemArr;
  }
}

const task = () => {
  let values = {};
  let file = require(`fs`).readFileSync(`./tests/input.txt`,`utf8`).toString().split(`\n`);
  let problem = file.shift().replace(/ /g, ``).split(/([$-/:-?{-~!"^_`\[\]])/g).filter((item) => item !== ``).map((item) => isNaN(Number(item)) ? item : Number(item));
  file.forEach((item) => values[item.split(` `)[0]] = Number(item.split(` `)[2]));
  problem.forEach((item, index) => Object.keys(values).includes(item) ? problem[index] = values[item] : item);
  console.log(...problem);
  console.log(values);
  // console.log(calculator(problem));
}

task();
