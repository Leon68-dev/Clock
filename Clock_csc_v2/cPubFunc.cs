using System;
using System.Collections;
using System.IO;
using System.Diagnostics;
using System.Runtime.InteropServices;


namespace Clock_csc_v2
{
	/// <summary>
	/// Summary description for cUbFunc.
	/// </summary>
	public class cPubFunc
	{
        public cPubFunc()
		{
			//
			// TODO: Add constructor logic here
			//
		}

		public static DateTime chkTime()
		{
			return (new DateTime(1900, 1, 1, 0, 0, 0));
		}

		public static string fileNameSet()
		{
			return Environment.CurrentDirectory + @"\clock_csc_v2.xml";
		}

        public static string getFileNameWav(string fileName)
        {
            return $"{Environment.CurrentDirectory}\\{fileName}";
        }

        public static System.Drawing.Color setColor(bool isBlack)
        {
            if (isBlack)
                return System.Drawing.Color.Black;
            else
                return System.Drawing.Color.WhiteSmoke;
        }

        public static bool existsWav(string filename)
        { 
            System.IO.FileInfo fTt = new System.IO.FileInfo(filename);
            return fTt.Exists;
        }

        ///////////////////////////////////////////////////////////////////////////////////////////////////////////
        #region Выключение ПК

        #region ShutdownFlag

        public const int Force = 0x00000004;

        /// EWX_FORCEIFHUNG
        /// </summary>
        public const int ForceIfHung = 0x00000010;

        /// EWX_LOGOFF
        public const int Logoff = 0x00000000;

        /// EWX_POWEROFF 
        public const int Poweroff = 0x00000008;

        /// EWX_REBOOT
        public const int Reboot = 0x00000002;

        /// EWX_SHUTDOWN
        public const int Shutdown = 0x00000001;

        [DllImport("user32.dll", SetLastError = true)]
        private static extern bool ExitWindowsEx(
            int flag,
            int reserved);

        /// <summary>
        /// Hibernate
        /// SetSuspendState(true, true, true);
        /// --------
        /// sleep
        /// SetSuspendState(false, true, true);
        /// </summary>
        /// <param name="hiberate"></param>
        /// <param name="forceCritical"></param>
        /// <param name="disableWakeEvent"></param>
        /// <returns></returns>
        [DllImport("PowrProf.dll", CharSet = CharSet.Auto, ExactSpelling = true)]
        public static extern bool SetSuspendState(
            bool hiberate, 
            bool forceCritical, 
            bool disableWakeEvent);

        [DllImport("user32")]
        public static extern void LockWorkStation();

        #endregion


        #region Privileges related Structures

        [StructLayout(LayoutKind.Sequential, Pack = 4)]
        public struct LUID_AND_ATTRIBUTES
        {
            public long Luid;
            public int Attributes;
        }

        [StructLayout(LayoutKind.Sequential, Pack = 4)]
        public struct TOKEN_PRIVILEGES
        {
            public int PrivilegeCount;
            public LUID_AND_ATTRIBUTES Privileges;
        }
        #endregion


        #region Privilege related APIs

        [DllImport("advapi32.dll", SetLastError = true)]
        private static extern bool OpenProcessToken(
            IntPtr ProcessHandle,
            int DesiredAccess,
            ref IntPtr TokenHandle);

        [DllImport("advapi32.dll", SetLastError = true)]
        private static extern bool LookupPrivilegeValue(
            string lpSystemName,
            string lpName,
            ref long lpLuid);

        [DllImport("advapi32.dll", SetLastError = true)]
        private static extern bool AdjustTokenPrivileges(
            IntPtr TokenHandle,
            bool DisableAllPrivileges,
            ref TOKEN_PRIVILEGES NewState,
            int BufferLength,
            IntPtr PreviousState,
            IntPtr ReturnLength
            );

        [DllImport("advapi32.dll", SetLastError = true)]
        private static extern bool InitiateSystemShutdown(
            string lpMachineName,
            string lpMessage,
            int dwTimeout,
            bool bForceAppsClosed,
            bool bRebootAfterShutdown
            );

        #endregion


        /// <summary>
        /// If the function succeeds, the return value is nonzero.
        /// </summary>
        /// <param name="flag"></param>
        /// <returns></returns>
        public static bool DoExitWindows(int flag)
        {
            try
            {
                /// Windows NT/2000/XP
                /// SE_SHUTDOWN_NAME
                if (System.Environment.OSVersion.Platform == PlatformID.Win32NT)
                    SetShutdownPrivilege();
                /// Windows Me 
                /// Explorer 
                /// EWX_LOGOFF 
                /// ExitWindowsEx() 
                else if (System.Environment.OSVersion.Platform == PlatformID.Win32Windows &&
                    ((flag & Force) == Force))
                    KillExplorer();
            }
            catch (Exception)
            {
                return false;
            }
            bool result = ExitWindowsEx(flag, 0);
            return result;
        }


        public static bool DoExitRemoteWindows(
            string compName,
            string msg,
            int time,
            bool force,
            bool reboot)
        {
            //SetRemoteShutdownPrivilege();

            if (InitiateSystemShutdown(compName, msg, time, force, reboot))
                return true;
            else
                return false;
        }


        /// <summary>
        /// Windows NT/2000/XP
        /// SE_SHUTDOWN_NAME
        /// SE_REMOTE_SHUTDOWN_NAME
        /// </summary>
        private static void SetShutdownPrivilege()
        {
            const int TOKEN_QUERY = 0x00000008;
            const int TOKEN_ADJUST_PRIVILEGES = 0x00000020;
            const string SE_SHUTDOWN_NAME = "SeShutdownPrivilege";
            const int SE_PRIVILEGE_ENABLED = 0x00000002;

            ///////////////////////////////////////////////////////////////////////////////////////
            const string SE_REMOTE_SHUTDOWN_NAME = "SeRemoteShutdownPrivilege";
            ///////////////////////////////////////////////////////////////////////////////////////

            IntPtr hproc = System.Diagnostics.Process.GetCurrentProcess().Handle;

            // Token
            IntPtr hToken = IntPtr.Zero;
            if (!OpenProcessToken(hproc, TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, ref hToken))
                throw new Exception("OpenProcessToken");

            // LUID 
            long luid = 0;
            if (!LookupPrivilegeValue(null, SE_SHUTDOWN_NAME, ref luid))
                throw new Exception("LookupPrivilegeValue");

            TOKEN_PRIVILEGES tp = new TOKEN_PRIVILEGES();
            tp.PrivilegeCount = 1;
            tp.Privileges = new LUID_AND_ATTRIBUTES();
            tp.Privileges.Luid = luid;
            tp.Privileges.Attributes = SE_PRIVILEGE_ENABLED;

            if (!AdjustTokenPrivileges(hToken, false, ref tp, 0, IntPtr.Zero, IntPtr.Zero))
                throw new Exception("AdjustTokenPrivileges");

            ///////////////////////////////////////////////////////////////////////////////////////
            if (!LookupPrivilegeValue(null, SE_REMOTE_SHUTDOWN_NAME, ref luid))
                throw new Exception("LookupPrivilegeValue");

            tp.PrivilegeCount = 1;
            tp.Privileges.Attributes = SE_PRIVILEGE_ENABLED;

            if (!AdjustTokenPrivileges(hToken, false, ref tp, 0, IntPtr.Zero, IntPtr.Zero))
                throw new Exception("AdjustTokenPrivileges");
            ///////////////////////////////////////////////////////////////////////////////////////

        }


        /// <summary>
        /// Windows Me 
        /// </summary>
        private static void KillExplorer()
        {
            // Windows Me 
            // ExitWindowsEx() 
            if (System.Environment.OSVersion.Platform == PlatformID.Win32Windows)
            {
                System.Diagnostics.Process[] processes = System.Diagnostics.Process.GetProcesses();
                foreach (Process process in processes)
                {
                    if (process.ProcessName.StartsWith("explorer"))
                        process.Kill();
                }
            }
        }


        /*	
            Пример выключения
            int flag = LWinAPI.cWinApi.cs.Poweroff; 
            LWinAPI.cWinApi.cs.DoExitWindows(flag); 
        */


        #endregion Выключение ПК


        ///////////////////////////////////////////////////////////////////////////////////////////////////////////
        #region Sound

        public const int SND_SYNC = 0x0000;             // грати синхронно (блокує)
        public const int SND_ASYNC = 0x0001;            // грати асинхронно (не блокує)
        public const int SND_NODEFAULT = 0x0002;        // не грати звук помилки, якщо файл не знайдено
        public const int SND_FILENAME = 0x00020000;     // перший параметр - це ім'я файлу
        public const int SND_PURGE = 0x0040;            // зупинити всі звуки

        /// <summary>
        /// Play sound file (winapi32)
        /// </summary>
        /// <param name="pszSound"></param>
        /// <param name="hmod"></param>
        /// <param name="fdwSound"></param>
        /// <returns></returns>
        [System.Runtime.InteropServices.DllImport("Winmm")]
        public static extern bool PlaySound(
            string pszSound,
            IntPtr hmod,
            int fdwSound);

        /// <summary>
        /// Play sound file
        /// </summary>
        /// <param name="soundFileName"></param>
        /// <returns></returns>
        public static bool playSound(string soundFileName, bool async = true)
        {
            bool r = false;
            try
            {
                if (!File.Exists(soundFileName)) 
                    return r;

                int flags = SND_FILENAME | SND_NODEFAULT;
                if (async) 
                    flags |= SND_ASYNC;

                r = PlaySound(soundFileName, IntPtr.Zero, flags);
            }
            catch (Exception ex) 
            {
                Debug.WriteLine(ex.Message);
                Debug.WriteLine(ex.StackTrace);
            }

            return r;
        }


        #endregion Sound

    }
}
