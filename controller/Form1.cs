using System;
using System.IO.Ports;
using System.Windows.Forms;
using SharpDX.XInput;

namespace PruebaControl
{
    public partial class Form1 : Form
    {
        private Controller controller;
        private System.Windows.Forms.Timer controllerTimer;
        private SerialPort spRecepcion;

        public Form1()
        {
            InitializeComponent();

            // Inicializa el controlador de Xbox
            controller = new Controller(UserIndex.One);

            if (!controller.IsConnected)
            {
                MessageBox.Show("El control de Xbox no está conectado.");
                return;
            }

            // Lista los puertos seriales disponibles en el comboBox al iniciar
            string[] availablePorts = SerialPort.GetPortNames();
            portOptionsBox.Items.AddRange(availablePorts);

            // Configura un Timer para revisar el estado del control periódicamente
            controllerTimer = new System.Windows.Forms.Timer();
            controllerTimer.Interval = 100; // 100 ms de intervalo
            controllerTimer.Tick += ControllerTimer_Tick;
        }

        private void portConnectBtn_Click(object sender, EventArgs e)
        {
            
        }

        private void ControllerTimer_Tick(object sender, EventArgs e)
        {
            var state = controller.GetState();
            double deadZoneThreshold = 0.2;
            double rightValue = state.Gamepad.RightThumbY / 32767.0;
            double leftValue = state.Gamepad.LeftThumbY / 32767.0;
            rightValue = Math.Abs(rightValue) < deadZoneThreshold ? 0 : rightValue;
            leftValue = Math.Abs(leftValue) < deadZoneThreshold ? 0 : leftValue;

            double scalingFactor = 0.7;
            rightValue *= scalingFactor;
            leftValue *= scalingFactor;

            
            double redRight = Math.Round(rightValue * 255);
            double redLeft = Math.Round(leftValue * 255);

           
            redRight *= -1;
            redLeft *= -1;

            try
            {
                if (spRecepcion.IsOpen)
                {
                    string message = $"{redRight} {redLeft}\n";
                    spRecepcion.WriteLine(message);
                    leftStatus.Text = redLeft.ToString();
                    rightStatus.Text = redRight.ToString();
                    Console.WriteLine($"Enviando: {message}");
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        private void DataReceivedHandler(object sender, SerialDataReceivedEventArgs e)
        {
            try
            {
                string receivedData = spRecepcion.ReadLine();
                Console.WriteLine($"Datos recibidos del Arduino: {receivedData}");
            }
            catch (Exception ex)
            {
                MessageBox.Show($"Error al leer del puerto serie: {ex.Message}");
            }
        }

        protected override void OnFormClosing(FormClosingEventArgs e)
        {
            if (spRecepcion != null && spRecepcion.IsOpen)
            {
                spRecepcion.Close();
            }
            base.OnFormClosing(e);
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void portConnectBtn_Click_1(object sender, EventArgs e)
        {
            if (portOptionsBox.SelectedItem != null)
            {
                string selectedPort = portOptionsBox.SelectedItem.ToString();
                spRecepcion = new SerialPort(selectedPort, 9600);
                spRecepcion.DataReceived += new SerialDataReceivedEventHandler(DataReceivedHandler);

                try
                {
                    spRecepcion.Open();
                    MessageBox.Show($"Conectado exitosamente al puerto {selectedPort}");
                    portConnectBtn.Enabled = false; // Deshabilitar el botón al conectarse
                    controllerTimer.Start(); // Iniciar el Timer
                }
                catch (Exception ex)
                {
                    MessageBox.Show($"Error al abrir el puerto serie: {ex.Message}");
                }
            }
            else
            {
                MessageBox.Show("Por favor selecciona un puerto antes de conectar.");
            }
        }
    }
}
