using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Xml;

namespace Project_Manager.Core
{
    class Editor
    {
        public Version Version;
        public string Path;
        public Editor(string path)
        {
            Version = new Version();
            Path = path;
        }
        public Editor(Version version, string path)
        { 
            Version = version;
            Path = path;
        }
    }
    struct Version
    {
        internal static Version zero = new Version(0, 0, 0);

        private short major;
        private short minor;
        private short subMinor;

        internal Version(short _major, short _minor, short _subMinor)
        {
            major = _major;
            minor = _minor;
            subMinor = _subMinor;
        }
        internal Version(string _version)
        {
            string[] versionStrings = _version.Split('.');
            if (versionStrings.Length != 3)
            {
                major = 0;
                minor = 0;
                subMinor = 0;
                return;
            }
            major = short.Parse(versionStrings[0]);
            minor = short.Parse(versionStrings[1]);
            subMinor = short.Parse(versionStrings[2]);
        }
        internal bool IsDifferentThan(Version other)
        {
            if (major != other.major)
            {
                return true;
            }
            else  if (minor != other.minor)
            {
                return true;
            }
            else if (subMinor != other.subMinor)
            {
                return true; 
            }
            
            return false;
        }
        public override readonly string ToString()
        {
            return $"{major}.{minor}.{subMinor}";
        }

    }

}
