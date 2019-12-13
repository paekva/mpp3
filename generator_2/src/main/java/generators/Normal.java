package generators;

public class Normal extends Generator {
    public Normal(double[] params){
        generatorParams = params;
    }

    double getRandomValue(double m, double y) {
        double N = 7;

        for (int i=0; i<N; i++) {
            y += Math.random();
            y -= N;
        }

        return m + y*y;
    }
}
