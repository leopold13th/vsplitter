pipeline {
    agent any
    stages {
        stage('build') {
            steps {
                cp ../build-vsplitter-Desktop-Debug/vsplitter ~/bin/
                echo "OK"
            }
        }
    }
}