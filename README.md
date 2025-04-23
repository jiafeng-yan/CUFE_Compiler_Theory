# A Course Design of Compiler Theory

## Usage
```bash
git clone git@github.com:jiafeng-yan/CUFE_Compiler_Theory.git
cd ./CUFE_Compiler_Theory
```
You can download the zip package alternatively.

## Enviroment
基于 Ubuntu24.04 实现
### install
```bash
sudo apt-get update
sudo apt-get install flex bison
```

### check
```bash
flex --version
bison --version
```


## Run
### LEX - count chars and lines   (Ex 1.1)
```bash
bash ./flex_/run.sh
```

### LEX - a simple syntax analyzer for Pascal     (Ex 1.2)
```bash
bash ./lex_for_PASCAL/run.sh
```

### Lexical Analyzer    (Ex 2)
```bash
bash ./lexical_analyzer/run.sh
```

### Grammatical Analyzer    (Ex 3)
```bash
bash ./grammatical_analyzer/run.sh
```
