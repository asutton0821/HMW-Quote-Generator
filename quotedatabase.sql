-- phpMyAdmin SQL Dump
-- version 4.5.4.1deb2ubuntu2.1
-- http://www.phpmyadmin.net
--
-- Host: localhost:3306
-- Generation Time: Sep 16, 2019 at 09:05 PM
-- Server version: 5.7.27-0ubuntu0.16.04.1
-- PHP Version: 7.0.33-0ubuntu0.16.04.6

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `quotedatabase`
--

-- --------------------------------------------------------

--
-- Table structure for table `authentication`
--

CREATE TABLE `authentication` (
  `userNum` int(11) NOT NULL,
  `username` text,
  `password` text,
  `userDescription` text,
  `salesPerson` int(11) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `authentication`
--

INSERT INTO `authentication` (`userNum`, `username`, `password`, `userDescription`, `salesPerson`) VALUES
(1, 'admin', 'íÞððôìïá', 'Administrator', 0),
(2, 'csutton', 'ñâðñ', 'Colson Sutton', 0),
(3, 'jeffhurdle', '', 'Jeff Hurdle', 1),
(4, 'johnhurdle', '', 'John Hurdle', 1),
(5, 'guest', '', 'Guest Account', 0),
(6, 'sales', 'ðÞéâð', 'Hurdle Sales', 1),
(7, 'BJ', 'íÞððôìïá', 'BJ', 0);

-- --------------------------------------------------------

--
-- Table structure for table `quoteItems`
--

CREATE TABLE `quoteItems` (
  `name` text,
  `quoteDescription` text NOT NULL,
  `price` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `quoteItems`
--

INSERT INTO `quoteItems` (`name`, `quoteDescription`, `price`) VALUES
('mill40LT', 'Magnum LT 40` Mill', 149850),
('mill48LT', 'Magnum LT 48` Mill', 158800),
('mill60LT', 'Magnum LT 60` Mill', 208800),
('mill40Chal', 'Challenger 40` Mill', 57700),
('mill48Chal', 'Challenger 48` Mill', 74950),
('mill60Chal', 'Challenger 60` Mill', 93450),
('extraAxle', 'Extra Axle/Wheels', 2500),
('cantTurner', 'Cant Turners', 3500),
('compSet', 'Computer Setworks', 15000),
('nanoSet', 'Nano Setworks', 5000),
('knee4Chal', 'Challenger 4 Knees', 16000),
('knee4LT', 'Magnum LT 4 Knees', 18500),
('hamDog', 'Hammer Dog', 4500),
('barLog', 'Bar Log Turner', 6500),
('hdChain', 'Heavy Duty Chain Log Turner', 3750),
('LD4Over3', '4 Strand Log Deck', 6500),
('LD3Over2', '3 Strand Log Deck', 2500),
('noLD2', 'No Log Deck', 6000),
('noLD3', 'No Log Deck', 8500),
('noLD4', 'No Log Deck', 10500),
('pulley36', '36 in Pulley and Bushing', 1180),
('hdOutfeed', 'Heavy Duty Outfeed Belt', 8500),
('sawDustChain', 'Sawdust Live Shaft (Bracket/Pulley/Belts)', 1500),
('vertEdg', 'Vertical Edger', 32000),
('feedJoyStick', 'Feed Joystick', 4750),
('topSaw', 'Top Saw', 18000),
('extraTrailer', 'Extra Trailer Leg', 500),
('linearCarriage', 'Linear Carriage', 85000),
('horiz', 'Horizontal Edger', 0),
('mill52LT', 'Magnum LT 52\' Mill', 166800),
('mill52Chal', 'Challenger 52\' Mill', 82950),
('brownsville', 'Brownsville Turner', 1000),
('checkBox', 'this is a test', 500),
('cantPushOff', 'Cant Push Off', 1000),
('linearCylinderCarriage', 'Linear Cylinder Carriage', 5000),
('magnumLinear', 'Magnum LT Linear', 6000),
('linearCompSetworks', 'Linear Computer setworks', 7000);

-- --------------------------------------------------------

--
-- Table structure for table `quoteOverrides`
--

CREATE TABLE `quoteOverrides` (
  `quoteNum` int(11) DEFAULT NULL,
  `name` text,
  `connectionName` text
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `quoteOverrides`
--

INSERT INTO `quoteOverrides` (`quoteNum`, `name`, `connectionName`) VALUES
(1, 'verticalEdgerCheckBox', 'vertEdg'),
(4, 'verticalEdgerCheckBox', 'vertEdg'),
(0, NULL, NULL),
(5, 'verticalEdgerCheckBox', 'vertEdg'),
(3, 'verticalEdgerCheckBox', 'vertEdg'),
(2, 'cantTurnersCheckBox', 'cantTurner'),
(0, NULL, NULL),
(3, 'topSawCheckBox', 'topSaw'),
(3, 'feedJoystickCheckBox', 'feedJoyStick'),
(0, NULL, NULL),
(5, 'hdCheckBox', 'hamDog'),
(7, 'verticalEdgerCheckBox', 'vertEdg'),
(3, 'hdOutfeedCheckBox', 'hdOutFeed');

-- --------------------------------------------------------

--
-- Table structure for table `quotes`
--

CREATE TABLE `quotes` (
  `quoteDate` text NOT NULL,
  `name` text NOT NULL,
  `quoteNum` int(11) NOT NULL,
  `handled` int(11) NOT NULL,
  `custom1` text,
  `custom2` text,
  `customPrice1` int(11) DEFAULT NULL,
  `customPrice2` int(11) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `quotes`
--

INSERT INTO `quotes` (`quoteDate`, `name`, `quoteNum`, `handled`, `custom1`, `custom2`, `customPrice1`, `customPrice2`) VALUES
('09/12/2019', 'adfsdf', 1, 0, '', '', 0, 0),
('09/12/2019', 'asd', 2, 0, '', '', 0, 0),
('09/14/2019', 'asdfdf', 3, 0, '', '', 0, 0),
('09/16/2019', 'fsdasd', 4, 0, '', '', 0, 0),
('09/16/2019', 'dfad', 5, 0, '', '', 0, 0);

-- --------------------------------------------------------

--
-- Table structure for table `quoteTable`
--

CREATE TABLE `quoteTable` (
  `quoteNum` int(11) DEFAULT NULL,
  `name` text,
  `connectionName` text,
  `value` text
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `quoteTable`
--

INSERT INTO `quoteTable` (`quoteNum`, `name`, `connectionName`, `value`) VALUES
(1, 'verticalEdgerCheckBox', 'vertEdg', '1'),
(1, 'stdChainRadioButton', 'standardChain', '1'),
(1, 'twoStrandDeckRadioButton', 'twoStrand', '1'),
(1, 'magnumRadioButton', 'magnumCarriage', '1'),
(1, 'platform40RadioButton', 'mill40', '1'),
(1, 'nameLineEdit', 'name', 'adfsdf'),
(1, 'companyNameLineEdit', 'compName', 'asdfasdf'),
(1, 'address1LineEdit', 'address1', 'asdfadfasdfa'),
(1, 'address2LineEdit', 'address2', 'adsfasdf'),
(1, 'cityLineEdit', 'city', 'adsfdsf'),
(1, 'emailLineEdit', 'email', 'asdfasdf'),
(1, 'phoneLineEdit', 'phone1', 'asdfasdf'),
(1, 'faxLineEdit', 'fax', 'adsfsdf'),
(1, 'dateEdit', 'date', '09/12/2019'),
(1, 'quoteNumLineEdit', 'quoteNum', '1'),
(1, 'salesPersonComboBox', 'salesP', 'Jeff Hurdle'),
(1, 'sawSpeedSpinBox', 'sawSpeed', '800'),
(1, 'carriageKneesSpinBox', 'knees', '2'),
(1, 'statusBox', 'status', 'Closed'),
(1, 'brownsvilleCheckBox', 'brownsville', '2'),
(1, 'cantPushOffCheckBox', 'cantPushOff', '2'),
(1, 'createdByConnection', 'createdBy', 'Administrator'),
(2, 'sawdustChainCheckBox', 'sawDustChain', '1'),
(2, 'hdCheckBox', 'hamDog', '1'),
(2, 'extraAxleCheckBox', 'extraAxle', '1'),
(2, 'stdChainRadioButton', 'standardChain', '1'),
(2, 'twoStrandDeckRadioButton', 'twoStrand', '1'),
(2, 'magnumRadioButton', 'magnumCarriage', '1'),
(2, 'platform40RadioButton', 'mill40', '1'),
(2, 'nameLineEdit', 'name', 'asd'),
(2, 'companyNameLineEdit', 'compName', 'asd'),
(2, 'address1LineEdit', 'address1', 'asd'),
(2, 'address2LineEdit', 'address2', 'asd'),
(2, 'cityLineEdit', 'city', 'adsasd'),
(2, 'emailLineEdit', 'email', 'asd'),
(2, 'phoneLineEdit', 'phone1', 'asd'),
(2, 'faxLineEdit', 'fax', 'asd'),
(2, 'dateEdit', 'date', '09/12/2019'),
(2, 'quoteNumLineEdit', 'quoteNum', '2'),
(2, 'salesPersonComboBox', 'salesP', 'Jeff Hurdle'),
(2, 'sawSpeedSpinBox', 'sawSpeed', '575'),
(2, 'carriageKneesSpinBox', 'knees', '2'),
(2, 'statusBox', 'status', 'Closed'),
(2, 'brownsvilleCheckBox', 'brownsville', '2'),
(2, 'createdByConnection', 'createdBy', 'Administrator'),
(3, 'feedJoystickCheckBox', 'feedJoyStick', '1'),
(3, 'hdOutfeedCheckBox', 'hdOutFeed', '1'),
(3, 'sawdustChainCheckBox', 'sawDustChain', '1'),
(3, 'cantTurnersCheckBox', 'cantTurner', '2'),
(3, 'stdChainRadioButton', 'standardChain', '1'),
(3, 'twoStrandDeckRadioButton', 'twoStrand', '1'),
(3, 'magnumRadioButton', 'magnumCarriage', '1'),
(3, 'platform40RadioButton', 'mill40', '1'),
(3, 'nameLineEdit', 'name', 'asdfdf'),
(3, 'companyNameLineEdit', 'compName', 'adsfadf'),
(3, 'address1LineEdit', 'address1', 'adfadf'),
(3, 'address2LineEdit', 'address2', 'adsfadsf'),
(3, 'cityLineEdit', 'city', 'adsfad'),
(3, 'emailLineEdit', 'email', 'adfadf'),
(3, 'stateComboBox', 'states', 'TN'),
(3, 'phoneLineEdit', 'phone1', 'adsfadf'),
(3, 'phone2LineEdit', 'phone2', 'adsfaf'),
(3, 'faxLineEdit', 'fax', 'adsfadf'),
(3, 'dateEdit', 'date', '09/14/2019'),
(3, 'quoteNumLineEdit', 'quoteNum', '3'),
(3, 'salesPersonComboBox', 'salesP', 'Jeff Hurdle'),
(3, 'sawSpeedSpinBox', 'sawSpeed', '575'),
(3, 'carriageKneesSpinBox', 'knees', '2'),
(3, 'statusBox', 'status', 'Open'),
(3, 'brownsvilleCheckBox', 'brownsville', '2'),
(3, 'cantPushOffCheckBox', 'cantPushOff', '2'),
(3, 'createdByConnection', 'createdBy', 'Administrator'),
(4, 'stdChainRadioButton', 'standardChain', '1'),
(4, 'threeStrandDeckRadioButton', 'threeStrand', '1'),
(4, 'magnumRadioButton', 'magnumCarriage', '1'),
(4, 'platform52RadioButton', 'mill52', '1'),
(4, 'nameLineEdit', 'name', 'fsdasd'),
(4, 'companyNameLineEdit', 'compName', 'sdafda'),
(4, 'address1LineEdit', 'address1', 'asfdas'),
(4, 'address2LineEdit', 'address2', 'asfda'),
(4, 'cityLineEdit', 'city', 'afdasf'),
(4, 'emailLineEdit', 'email', 'safda'),
(4, 'stateComboBox', 'states', 'AL'),
(4, 'phoneLineEdit', 'phone1', 'dadfa'),
(4, 'phone2LineEdit', 'phone2', 'adfa'),
(4, 'faxLineEdit', 'fax', 'asdfa'),
(4, 'dateEdit', 'date', '09/16/2019'),
(4, 'quoteNumLineEdit', 'quoteNum', '4'),
(4, 'salesPersonComboBox', 'salesP', 'Jeff Hurdle'),
(4, 'sawSpeedSpinBox', 'sawSpeed', '575'),
(4, 'carriageKneesSpinBox', 'knees', '3'),
(4, 'statusBox', 'status', 'Open'),
(4, 'linearCheckBox', 'linearCarriage', '1'),
(4, 'linearCylinderCarriageCheckBox', 'linearCylinderCarriage', '1'),
(4, 'createdByConnection', 'createdBy', 'Administrator'),
(5, 'compsetRadioButton', 'compSet', '1'),
(5, 'stdChainRadioButton', 'standardChain', '1'),
(5, 'twoStrandDeckRadioButton', 'twoStrand', '1'),
(5, 'magnumRadioButton', 'magnumCarriage', '1'),
(5, 'platform40RadioButton', 'mill40', '1'),
(5, 'nameLineEdit', 'name', 'dfad'),
(5, 'companyNameLineEdit', 'compName', 'fasdfdaf'),
(5, 'address1LineEdit', 'address1', 'saddfaf'),
(5, 'address2LineEdit', 'address2', 'safdasf'),
(5, 'cityLineEdit', 'city', 'asfddasf'),
(5, 'emailLineEdit', 'email', 'afadf'),
(5, 'phoneLineEdit', 'phone1', 'asfda'),
(5, 'faxLineEdit', 'fax', 'faf'),
(5, 'dateEdit', 'date', '09/16/2019'),
(5, 'quoteNumLineEdit', 'quoteNum', '5'),
(5, 'salesPersonComboBox', 'salesP', 'Jeff Hurdle'),
(5, 'sawSpeedSpinBox', 'sawSpeed', '575'),
(5, 'carriageKneesSpinBox', 'knees', '2'),
(5, 'statusBox', 'status', 'Open'),
(5, 'linearCheckBox', 'linearCarriage', '1'),
(5, 'magnumLinearCheckBox', 'magnumLinear', '1'),
(5, 'createdByConnection', 'createdBy', 'Administrator');

--
-- Indexes for dumped tables
--

--
-- Indexes for table `authentication`
--
ALTER TABLE `authentication`
  ADD PRIMARY KEY (`userNum`);

--
-- Indexes for table `quotes`
--
ALTER TABLE `quotes`
  ADD PRIMARY KEY (`quoteNum`);

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
