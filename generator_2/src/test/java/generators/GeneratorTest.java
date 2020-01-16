package generators;

import org.junit.BeforeClass;
import org.junit.Ignore;
import org.junit.Test;
import types.EType;
import types.ModeType;

import static org.junit.Assert.*;
import java.util.Arrays;

public class GeneratorTest {

    private static Uniform uniform;
    private static Normal normal;
    private static Exponential exponential;

    private static boolean isInteger(double number){
        return number == Math.round(number);
    }

    @BeforeClass
    public static void preTest(){
        double[] params = new double[]{1, 4};
        uniform = new Uniform(params);
        normal = new Normal(params);
        exponential = new Exponential(1);
    }

    @Test
    public void getRandomValueFromUniformDistribution() {
        EType result = uniform.getMessageType();
        assertTrue(Arrays.asList(EType.values()).contains(result));
    }

    @Test
    public void getRandomValueFromNormalDistribution() {
        double result = normal.getRandomValue();
        assertTrue(result > 0);
    }

    @Test
    @Ignore
    public void getRandomValueFromExponentialDistribution() {
        double result = exponential.getRandomValue();
        assertTrue(result > 0);
    }

    @Test
    public void getArraySize() {
        int uniformSize = uniform.getArraySize();
        assertTrue(uniformSize > 0 && isInteger(uniformSize));

        int normalSize = normal.getArraySize();
        assertTrue(normalSize > 0 && isInteger(normalSize));

        int expSize = exponential.getArraySize();
        assertTrue(expSize > 0 && isInteger(expSize));
    }

    @Test
    public void getMessagesCount() {
        int uniformSize = uniform.getArraySize();
        assertTrue(uniformSize > 0 && isInteger(uniformSize));

        int normalSize = normal.getArraySize();
        assertTrue(normalSize > 0 && isInteger(normalSize));

        int expSize = exponential.getArraySize();
        assertTrue(expSize > 0 && isInteger(expSize));
    }

    @Test
    public void initUniformGeneratorTest(){
        Generator generator = Generator.initGenerator(ModeType.UNIFORM, new double[2]);
        assertTrue(generator instanceof Uniform);
    }

    @Test
    public void initNormalGeneratorTest(){
        Generator generator = Generator.initGenerator(ModeType.NORMAL, new double[2]);
        assertTrue(generator instanceof Normal);
    }

    @Test
    public void initExponentialGeneratorTest(){
        Generator generator = Generator.initGenerator(ModeType.EXPONENTIAL, new double[2]);
        assertTrue(generator instanceof Exponential);
    }
}