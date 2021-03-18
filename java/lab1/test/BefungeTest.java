import java.io.InputStream;

import static org.junit.jupiter.api.Assertions.*;

class BefungeTest {

    @org.junit.jupiter.api.Test
    void isFinished() {
        Befunge bef = new Befunge();
        StringBuilder string = new StringBuilder("");
        String[] buf = {""};
        String[] argv = {"C:\\Users\\aleks\\IdeaProjects\\TestBefunge\\src\\main\\resources\\isFinished.txt"};
        bef.interpret(argv, new ContextIOForTest(string, buf));
        assertEquals(0, bef.sizeForTest());
        assertTrue(bef.jobIsFinishedForTest());
        assertEquals("", string.toString());
    }

    @org.junit.jupiter.api.Test
    void noArguments() {
        Befunge bef = new Befunge();
        StringBuilder string = new StringBuilder("");
        String[] buf = {""};
        String[] argv = {};
        bef.interpret(argv, new ContextIOForTest(string, buf));
        assertTrue(string.toString().equals("Needs argument"));
    }

    @org.junit.jupiter.api.Test
    void noSuchFile() {
        Befunge bef = new Befunge();
        StringBuilder string = new StringBuilder("");
        String[] buf = {""};
        String[] argv = {"nothing"};
        bef.interpret(argv, new ContextIOForTest(string, buf));
        assertTrue(string.toString().equals("Can't find file nothing"));
    }

    @org.junit.jupiter.api.Test
    void noSuchCommand() {
        Befunge bef = new Befunge();
        StringBuilder string = new StringBuilder("");
        String[] buf = {""};
        String[] argv = {"C:\\Users\\aleks\\IdeaProjects\\TestBefunge\\src\\main\\resources\\noSuchCommand"};
        bef.interpret(argv, new ContextIOForTest(string, buf));
        assertTrue(string.toString().equals("Can't use command y"));
    }

    @org.junit.jupiter.api.Test
    void putter() {
        Befunge bef = new Befunge();
        StringBuilder string = new StringBuilder("");
        String[] buf = {""};
        String[] argv = {"C:\\Users\\aleks\\IdeaProjects\\TestBefunge\\src\\main\\resources\\putter.txt"};
        bef.interpret(argv, new ContextIOForTest(string, buf));
        assertEquals(3, bef.sizeForTest());
        assertEquals(3, bef.getForTest());
        bef.popForTest();
        assertEquals(2, bef.getForTest());
        bef.popForTest();
        assertEquals(1, bef.getForTest());
        bef.popForTest();
        assertEquals(0, bef.sizeForTest());
        assertEquals("", string.toString());
        assertTrue(bef.jobIsFinishedForTest());
    }

    @org.junit.jupiter.api.Test
    void AdditionOk() {
        Befunge bef = new Befunge();
        StringBuilder string = new StringBuilder("");
        String[] buf = {""};
        String[] argv = {"C:\\Users\\aleks\\IdeaProjects\\TestBefunge\\src\\main\\resources\\AdditionOk.txt"};
        bef.interpret(argv, new ContextIOForTest(string, buf));
        assertEquals(3, bef.sizeForTest());
        assertEquals(11, bef.getForTest());
        assertEquals("", string.toString());
        assertTrue(bef.jobIsFinishedForTest());
    }

    @org.junit.jupiter.api.Test
    void AdditionError() {
        Befunge bef = new Befunge();
        StringBuilder string = new StringBuilder("");
        String[] buf = {""};
        String[] argv = {"C:\\Users\\aleks\\IdeaProjects\\TestBefunge\\src\\main\\resources\\AdditionError.txt"};
        bef.interpret(argv, new ContextIOForTest(string, buf));
        assertEquals("java.lang.RuntimeException: Addition needs 2 operands", string.toString());
    }

    @org.junit.jupiter.api.Test
    void SubtractionOk() {
        Befunge bef = new Befunge();
        StringBuilder string = new StringBuilder("");
        String[] buf = {""};
        String[] argv = {"C:\\Users\\aleks\\IdeaProjects\\TestBefunge\\src\\main\\resources\\SubtractionOk.txt"};
        bef.interpret(argv, new ContextIOForTest(string, buf));
        assertEquals(3, bef.sizeForTest());
        assertEquals(1, bef.getForTest());
        assertEquals("", string.toString());
        assertTrue(bef.jobIsFinishedForTest());
    }

    @org.junit.jupiter.api.Test
    void SubtractionError() {
        Befunge bef = new Befunge();
        StringBuilder string = new StringBuilder("");
        String[] buf = {""};
        String[] argv = {"C:\\Users\\aleks\\IdeaProjects\\TestBefunge\\src\\main\\resources\\SubtractionError.txt"};
        bef.interpret(argv, new ContextIOForTest(string, buf));
        assertEquals("java.lang.RuntimeException: Subtraction needs 2 operands", string.toString());
    }

    @org.junit.jupiter.api.Test
    void MultiplicationOk() {
        Befunge bef = new Befunge();
        StringBuilder string = new StringBuilder("");
        String[] buf = {""};
        String[] argv = {"C:\\Users\\aleks\\IdeaProjects\\TestBefunge\\src\\main\\resources\\MultiplicationOk.txt"};
        bef.interpret(argv, new ContextIOForTest(string, buf));
        assertEquals(3, bef.sizeForTest());
        assertEquals(63, bef.getForTest());
        assertEquals("", string.toString());
        assertTrue(bef.jobIsFinishedForTest());
    }

    @org.junit.jupiter.api.Test
    void MultiplicationError() {
        Befunge bef = new Befunge();
        StringBuilder string = new StringBuilder("");
        String[] buf = {""};
        String[] argv = {"C:\\Users\\aleks\\IdeaProjects\\TestBefunge\\src\\main\\resources\\MultiplicationError.txt"};
        bef.interpret(argv, new ContextIOForTest(string, buf));
        assertEquals("java.lang.RuntimeException: Multiplication needs 2 operands", string.toString());
    }

    @org.junit.jupiter.api.Test
    void DivisionOk() {
        Befunge bef = new Befunge();
        StringBuilder string = new StringBuilder("");
        String[] buf = {""};
        String[] argv = {"C:\\Users\\aleks\\IdeaProjects\\TestBefunge\\src\\main\\resources\\DivisionOk.txt"};
        bef.interpret(argv, new ContextIOForTest(string, buf));
        assertEquals(3, bef.sizeForTest());
        assertEquals(2, bef.getForTest());
        assertEquals("", string.toString());
        assertTrue(bef.jobIsFinishedForTest());
    }

    @org.junit.jupiter.api.Test
    void DivisionError() {
        Befunge bef = new Befunge();
        StringBuilder string = new StringBuilder("");
        String[] buf = {""};
        String[] argv = {"C:\\Users\\aleks\\IdeaProjects\\TestBefunge\\src\\main\\resources\\DivisionError.txt"};
        bef.interpret(argv, new ContextIOForTest(string, buf));
        assertEquals("java.lang.RuntimeException: Division needs 2 operands", string.toString());
    }

    @org.junit.jupiter.api.Test
    void DivisionByZero() {
        Befunge bef = new Befunge();
        StringBuilder string = new StringBuilder("");
        String[] buf = {""};
        String[] argv = {"C:\\Users\\aleks\\IdeaProjects\\TestBefunge\\src\\main\\resources\\DivisionbyZero.txt"};
        bef.interpret(argv, new ContextIOForTest(string, buf));
        assertEquals("java.lang.RuntimeException: Division by zero", string.toString());
    }

    @org.junit.jupiter.api.Test
    void ModuloOk() {
        Befunge bef = new Befunge();
        StringBuilder string = new StringBuilder("");
        String[] buf = {""};
        String[] argv = {"C:\\Users\\aleks\\IdeaProjects\\TestBefunge\\src\\main\\resources\\ModuloOk.txt"};
        bef.interpret(argv, new ContextIOForTest(string, buf));
        assertEquals(3, bef.sizeForTest());
        assertEquals(1, bef.getForTest());
        assertEquals("", string.toString());
        assertTrue(bef.jobIsFinishedForTest());
    }

    @org.junit.jupiter.api.Test
    void ModuloError() {
        Befunge bef = new Befunge();
        StringBuilder string = new StringBuilder("");
        String[] buf = {""};
        String[] argv = {"C:\\Users\\aleks\\IdeaProjects\\TestBefunge\\src\\main\\resources\\ModuloError.txt"};
        bef.interpret(argv, new ContextIOForTest(string, buf));
        assertEquals("java.lang.RuntimeException: Modulo needs 2 operands", string.toString());
    }

    @org.junit.jupiter.api.Test
    void ModuloByZero() {
        Befunge bef = new Befunge();
        StringBuilder string = new StringBuilder("");
        String[] buf = {""};
        String[] argv = {"C:\\Users\\aleks\\IdeaProjects\\TestBefunge\\src\\main\\resources\\moduloByZero.txt"};
        bef.interpret(argv, new ContextIOForTest(string, buf));
        assertEquals("java.lang.RuntimeException: % by zero", string.toString());
    }

    @org.junit.jupiter.api.Test
    void NegationOk() {
        Befunge bef = new Befunge();
        StringBuilder string = new StringBuilder("");
        String[] buf = {""};
        String[] argv = {"C:\\Users\\aleks\\IdeaProjects\\TestBefunge\\src\\main\\resources\\NegationOk.txt"};
        bef.interpret(argv, new ContextIOForTest(string, buf));
        assertEquals(3, bef.sizeForTest());
        assertEquals(1, bef.getForTest());
        bef.popForTest();
        assertEquals(0, bef.getForTest());
        assertEquals("", string.toString());
        assertTrue(bef.jobIsFinishedForTest());
    }

    @org.junit.jupiter.api.Test
    void NegationError() {
        Befunge bef = new Befunge();
        StringBuilder string = new StringBuilder("");
        String[] buf = {""};
        String[] argv = {"C:\\Users\\aleks\\IdeaProjects\\TestBefunge\\src\\main\\resources\\NegationError.txt"};
        bef.interpret(argv, new ContextIOForTest(string, buf));
        assertEquals("java.lang.RuntimeException: Stack is empty", string.toString());
    }

    @org.junit.jupiter.api.Test
    void ComparerOk() {
        Befunge bef = new Befunge();
        StringBuilder string = new StringBuilder("");
        String[] buf = {""};
        String[] argv = {"C:\\Users\\aleks\\IdeaProjects\\TestBefunge\\src\\main\\resources\\ComparerOk.txt"};
        bef.interpret(argv, new ContextIOForTest(string, buf));
        assertEquals(4, bef.sizeForTest());
        assertEquals(0, bef.getForTest());
        bef.popForTest();
        assertEquals(1, bef.getForTest());
        assertEquals("", string.toString());
        assertTrue(bef.jobIsFinishedForTest());
    }

    @org.junit.jupiter.api.Test
    void ComparerError() {
        Befunge bef = new Befunge();
        StringBuilder string = new StringBuilder("");
        String[] buf = {""};
        String[] argv = {"C:\\Users\\aleks\\IdeaProjects\\TestBefunge\\src\\main\\resources\\ComparerError.txt"};
        bef.interpret(argv, new ContextIOForTest(string, buf));
        assertEquals("java.lang.RuntimeException: Comparer needs 2 operands", string.toString());
    }

    @org.junit.jupiter.api.Test
    void Navigator() {
        Befunge bef = new Befunge();
        StringBuilder string = new StringBuilder("");
        String[] buf = {""};
        String[] argv = {"C:\\Users\\aleks\\IdeaProjects\\TestBefunge\\src\\main\\resources\\Navigator.txt"};
        bef.interpret(argv, new ContextIOForTest(string, buf));
        assertEquals(4, bef.sizeForTest());
        assertEquals(4, bef.getForTest());
        bef.popForTest();
        assertEquals(3, bef.getForTest());
        bef.popForTest();
        assertEquals(2, bef.getForTest());
        bef.popForTest();
        assertEquals(1, bef.getForTest());
        assertEquals("", string.toString());
        assertTrue(bef.jobIsFinishedForTest());
    }

    @org.junit.jupiter.api.Test
    void If() {
        Befunge bef = new Befunge();
        StringBuilder string = new StringBuilder("");
        String[] buf = {""};
        String[] argv = {"C:\\Users\\aleks\\IdeaProjects\\TestBefunge\\src\\main\\resources\\If.txt"};
        bef.interpret(argv, new ContextIOForTest(string, buf));
        assertEquals(5, bef.sizeForTest());
        assertEquals(1, bef.getForTest());
        bef.popForTest();
        assertEquals(1, bef.getForTest());
        bef.popForTest();
        assertEquals(0, bef.getForTest());
        bef.popForTest();
        assertEquals(0, bef.getForTest());
        bef.popForTest();
        assertEquals(1, bef.getForTest());
        assertEquals("", string.toString());
        assertTrue(bef.jobIsFinishedForTest());
    }

    @org.junit.jupiter.api.Test
    void VerticalIfError() {
        Befunge bef = new Befunge();
        StringBuilder string = new StringBuilder("");
        String[] buf = {""};
        String[] argv = {"C:\\Users\\aleks\\IdeaProjects\\TestBefunge\\src\\main\\resources\\VerticalIfError.txt"};
        bef.interpret(argv, new ContextIOForTest(string, buf));
        assertEquals("java.lang.RuntimeException: Stack is empty", string.toString());
    }

    @org.junit.jupiter.api.Test
    void GorizontalIfError() {
        Befunge bef = new Befunge();
        StringBuilder string = new StringBuilder("");
        String[] buf = {""};
        String[] argv = {"C:\\Users\\aleks\\IdeaProjects\\TestBefunge\\src\\main\\resources\\GorizontalIfError.txt"};
        bef.interpret(argv, new ContextIOForTest(string, buf));
        assertEquals("java.lang.RuntimeException: Stack is empty", string.toString());
    }

    @org.junit.jupiter.api.Test
    void StringMode() {
        Befunge bef = new Befunge();
        StringBuilder string = new StringBuilder("");
        String[] buf = {""};
        String[] argv = {"C:\\Users\\aleks\\IdeaProjects\\TestBefunge\\src\\main\\resources\\StringMode.txt"};
        bef.interpret(argv, new ContextIOForTest(string, buf));
        assertEquals("test string mode", string.toString());
    }

    @org.junit.jupiter.api.Test
    void DuplicatorOk() {
        Befunge bef = new Befunge();
        StringBuilder string = new StringBuilder("");
        String[] buf = {""};
        String[] argv = {"C:\\Users\\aleks\\IdeaProjects\\TestBefunge\\src\\main\\resources\\DuplicatorOk.txt"};
        bef.interpret(argv, new ContextIOForTest(string, buf));
        assertEquals(2, bef.sizeForTest());
        assertEquals(5, bef.getForTest());
        bef.popForTest();
        assertEquals(5, bef.getForTest());
        assertEquals("", string.toString());
        assertTrue(bef.jobIsFinishedForTest());
    }

    @org.junit.jupiter.api.Test
    void DuplicatorError() {
        Befunge bef = new Befunge();
        StringBuilder string = new StringBuilder("");
        String[] buf = {""};
        String[] argv = {"C:\\Users\\aleks\\IdeaProjects\\TestBefunge\\src\\main\\resources\\DuplicatorError.txt"};
        bef.interpret(argv, new ContextIOForTest(string, buf));
        assertEquals("java.lang.RuntimeException: Stack is empty", string.toString());
    }

    @org.junit.jupiter.api.Test
    void Randomizer() {
        Befunge bef = new Befunge();
        StringBuilder string = new StringBuilder("");
        String[] buf = {""};
        String[] argv = {"C:\\Users\\aleks\\IdeaProjects\\TestBefunge\\src\\main\\resources\\Randomizer.txt"};
        bef.interpret(argv, new ContextIOForTest(string, buf));
        assertEquals("", string.toString());
        assertTrue(bef.jobIsFinishedForTest());
    }

    @org.junit.jupiter.api.Test
    void SwapperOk() {
        Befunge bef = new Befunge();
        StringBuilder string = new StringBuilder("");
        String[] buf = {""};
        String[] argv = {"C:\\Users\\aleks\\IdeaProjects\\TestBefunge\\src\\main\\resources\\SwapperOk.txt"};
        bef.interpret(argv, new ContextIOForTest(string, buf));
        assertEquals(2, bef.sizeForTest());
        assertEquals(1, bef.getForTest());
        bef.popForTest();
        assertEquals(2, bef.getForTest());
        assertEquals("", string.toString());
        assertTrue(bef.jobIsFinishedForTest());
    }

    @org.junit.jupiter.api.Test
    void SwapperError() {
        Befunge bef = new Befunge();
        StringBuilder string = new StringBuilder("");
        String[] buf = {""};
        String[] argv = {"C:\\Users\\aleks\\IdeaProjects\\TestBefunge\\src\\main\\resources\\SwapperError.txt"};
        bef.interpret(argv, new ContextIOForTest(string, buf));
        assertEquals("java.lang.RuntimeException: Swapper needs 2 operands", string.toString());
    }

    @org.junit.jupiter.api.Test
    void Popper() {
        Befunge bef = new Befunge();
        StringBuilder string = new StringBuilder("");
        String[] buf = {""};
        String[] argv = {"C:\\Users\\aleks\\IdeaProjects\\TestBefunge\\src\\main\\resources\\Popper.txt"};
        bef.interpret(argv, new ContextIOForTest(string, buf));
        assertEquals(0, bef.sizeForTest());
        assertEquals("", string.toString());
        assertTrue(bef.jobIsFinishedForTest());
    }

    @org.junit.jupiter.api.Test
    void OutputterInt() {
        Befunge bef = new Befunge();
        StringBuilder string = new StringBuilder("");
        String[] buf = {""};
        String[] argv = {"C:\\Users\\aleks\\IdeaProjects\\TestBefunge\\src\\main\\resources\\OutputterInt.txt"};
        bef.interpret(argv, new ContextIOForTest(string, buf));
        assertEquals(1, bef.sizeForTest());
        assertEquals("4", string.toString());
        assertTrue(bef.jobIsFinishedForTest());
    }

    @org.junit.jupiter.api.Test
    void OutputterChar() {
        Befunge bef = new Befunge();
        StringBuilder string = new StringBuilder("");
        String[] buf = {""};
        String[] argv = {"C:\\Users\\aleks\\IdeaProjects\\TestBefunge\\src\\main\\resources\\OutputterChar.txt"};
        bef.interpret(argv, new ContextIOForTest(string, buf));
        assertEquals(5, bef.sizeForTest());
        assertEquals("A", string.toString());
        assertTrue(bef.jobIsFinishedForTest());
    }

    @org.junit.jupiter.api.Test
    void Skipper() {
        Befunge bef = new Befunge();
        StringBuilder string = new StringBuilder("");
        String[] buf = {""};
        String[] argv = {"C:\\Users\\aleks\\IdeaProjects\\TestBefunge\\src\\main\\resources\\Skipper.txt"};
        bef.interpret(argv, new ContextIOForTest(string, buf));
        assertEquals(2, bef.sizeForTest());
        assertEquals(2, bef.getForTest());
        bef.popForTest();
        assertEquals(1, bef.getForTest());
        assertEquals("", string.toString());
        assertTrue(bef.jobIsFinishedForTest());
    }

    @org.junit.jupiter.api.Test
    void GetterError() {
        Befunge bef = new Befunge();
        StringBuilder string = new StringBuilder("");
        String[] buf = {""};
        String[] argv = {"C:\\Users\\aleks\\IdeaProjects\\TestBefunge\\src\\main\\resources\\GetterError.txt"};
        bef.interpret(argv, new ContextIOForTest(string, buf));
        assertEquals("java.lang.RuntimeException: Getter needs 2 operands", string.toString());
    }

    @org.junit.jupiter.api.Test
    void GetterOk() {
        Befunge bef = new Befunge();
        StringBuilder string = new StringBuilder("");
        String[] buf = {""};
        String[] argv = {"C:\\Users\\aleks\\IdeaProjects\\TestBefunge\\src\\main\\resources\\GetterOk.txt"};
        bef.interpret(argv, new ContextIOForTest(string, buf));
        assertEquals(3, bef.sizeForTest());
        assertEquals(65, bef.getForTest());
        bef.popForTest();
        assertEquals(0, bef.getForTest());
        bef.popForTest();
        assertEquals(0, bef.getForTest());
        assertTrue(bef.jobIsFinishedForTest());
        assertEquals("", string.toString());
    }

    @org.junit.jupiter.api.Test
    void ModificatorError() {
        Befunge bef = new Befunge();
        StringBuilder string = new StringBuilder("");
        String[] buf = {""};
        String[] argv = {"C:\\Users\\aleks\\IdeaProjects\\TestBefunge\\src\\main\\resources\\ModificatorError.txt"};
        bef.interpret(argv, new ContextIOForTest(string, buf));
        assertEquals("java.lang.RuntimeException: Modificator needs 3 operands", string.toString());
    }

    @org.junit.jupiter.api.Test
    void ModificatorOk() {
        Befunge bef = new Befunge();
        StringBuilder string = new StringBuilder("");
        String[] buf = {""};
        String[] argv = {"C:\\Users\\aleks\\IdeaProjects\\TestBefunge\\src\\main\\resources\\ModificatorOk.txt"};
        bef.interpret(argv, new ContextIOForTest(string, buf));
        assertEquals(5, bef.sizeForTest());
        assertEquals('@', (char)bef.getForTest());
        bef.popForTest();
        assertEquals(8, bef.getForTest());
        bef.popForTest();
        assertEquals(1, bef.getForTest());
        bef.popForTest();
        assertEquals(0, bef.getForTest());
        bef.popForTest();
        assertEquals(0, bef.getForTest());
        assertTrue(bef.jobIsFinishedForTest());
        assertEquals("", string.toString());
    }

    @org.junit.jupiter.api.Test
    void ReaderInt() {
        Befunge bef = new Befunge();
        StringBuilder string = new StringBuilder("");
        String[] buf = {"9"};
        String[] argv = {"C:\\Users\\aleks\\IdeaProjects\\TestBefunge\\src\\main\\resources\\ReaderInt.txt"};
        bef.interpret(argv, new ContextIOForTest(string, buf));
        assertEquals(1, bef.sizeForTest());
        assertEquals(9, bef.getForTest());
        assertTrue(bef.jobIsFinishedForTest());
        assertEquals("", string.toString());
    }

    @org.junit.jupiter.api.Test
    void ReaderChar() {
        Befunge bef = new Befunge();
        StringBuilder string = new StringBuilder("");
        String[] buf = {"A"};
        String[] argv = {"C:\\Users\\aleks\\IdeaProjects\\TestBefunge\\src\\main\\resources\\ReaderChar.txt"};
        bef.interpret(argv, new ContextIOForTest(string, buf));
        assertEquals(1, bef.sizeForTest());
        assertEquals('A', (char)bef.getForTest());
        assertTrue(bef.jobIsFinishedForTest());
        assertEquals("", string.toString());
    }

    @org.junit.jupiter.api.Test
    void FactoryBuf() {
        InputStream in = Befunge.class.getClassLoader().getResourceAsStream("properties.txt");
        Factory.getInstance().configurate(in);
        Factory.getInstance().getCommand(String.valueOf('@'));
        Factory.getInstance().getCommand(String.valueOf('p'));
        Factory.getInstance().getCommand(String.valueOf('p'));
        Factory.getInstance().getCommand(String.valueOf('\''));
        Factory.getInstance().getCommand(String.valueOf('@'));
        Factory.getInstance().getCommand(String.valueOf('\''));
        assertEquals(3, Factory.getInstance().getSizeForTest());
    }
}