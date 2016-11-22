# SOSE-WSDL

##Authors
EzpzCraft - https://github.com/EzpzCraft/
HerrAugust - https://github.com/HerrAugust/

## Tutorial files
You wan find here the source code for each step of the tutorial.
The final wsdl file is `weather.wsdl`

### Step 1: root definition

```xml
<?xml version="1.0" encoding="UTF-8" standalone="no"?>
<wsdl:definitions 	xmlns:soap="http://schemas.xmlsoap.org/wsdl/soap/" 
					xmlns:tns="http://www.example.org/weather/" 
					xmlns:wsdl="http://schemas.xmlsoap.org/wsdl/" 
					xmlns:xs="http://www.w3.org/2001/XMLSchema" 
					name="weather" 
					targetNamespace="http://www.example.org/weather/">

  <!-- Definitions go here -->
</wsdl:definitions>
```

### Step 2: types definition
```xml
  <wsdl:types>
    <xs:schema targetNamespace="http://www.example.org/weather/">      
      <!-- Date -->
	  <xs:element name="date" type="xs:date"/>      
      <!-- Location (GPS) -->
      <xs:element name="location">
		<xs:complexType>
		  <xs:sequence>
			<xs:element name="longitude" type="xs:decimal"/>
			<xs:element name="latitude" type="xs:decimal"/>
		  </xs:sequence>
		</xs:complexType>
	  </xs:element>
	  <!-- Temperature (°C) -->
      <xs:element name="temperature" type="xs:decimal"/>
      <!-- Wind Speed (km/h) -->
      <xs:element name="wind" type="xs:decimal"/>
      <!-- Humidity (%) -->
      <xs:element name="humidity" type="xs:decimal"/>
      <!-- Sky = {sunny, cloudy, fog} -->            
	  <xs:element name="sky">
		<xs:simpleType>
		  <xs:restriction base="xs:string">
			  <xs:enumeration value="sunny"/>
			  <xs:enumeration value="cloudy"/>
		    <xs:enumeration value="fog"/>
		  </xs:restriction>
		</xs:simpleType>
	  </xs:element>    
    </xs:schema>
  </wsdl:types>
```

### Step 3: messages definition
```xml
  <!-- LocationMessage -->
  <wsdl:message name="locationMessage">
  	<wsdl:part name="arg" element="tns:location"/>
  </wsdl:message>
  <!-- WeatherMessage -->
  <wsdl:message name="weatherMessage">
    <wsdl:part name="date" element="tns:date"/>
    <wsdl:part name="temperature" element="tns:temperature"/>
    <wsdl:part name="wind" element="tns:wind"/>
    <wsdl:part name="humidity" element="tns:humidity"/>
    <wsdl:part name="sky" element="tns:sky"/>
  </wsdl:message>
```

### Step 4: port type and operations definition
```xml
  <wsdl:portType name="WeatherPortType">
    <!-- Subscribe -->
    <wsdl:operation name="subscribeWeather">
      <wsdl:input message="tns:locationMessage"/>
    </wsdl:operation>
    <!-- Get -->
    <wsdl:operation name="getWeather">
      <wsdl:input message="tns:locationMessage"/>
      <wsdl:output message="tns:weatherMessage"/>
    </wsdl:operation>
    <!-- Update -->
    <wsdl:operation name="updateWeather">
  	  <wsdl:output message="tns:locationMessage"/>
      <wsdl:input message="tns:weatherMessage"/>
    </wsdl:operation>
    <!-- Alert -->
	<wsdl:operation name="alertWeather">
	  <wsdl:output message="tns:weatherMessage"/>
    </wsdl:operation>
  </wsdl:portType>
```

### Step 5: binding definition (without extensibility elements)
```xml
<wsdl:binding type="tns:WeatherPortType" name="WeatherBinding">
      <soap:binding style="document" transport="http://schemas.xmlsoap.org/soap/http"/>      
      <wsdl:operation name="subscribeWeather">
        <soap:operation soapAction="http://www.example.org/weather/subscribeWeather"/>
        <wsdl:input>
          <soap:body parts="arg" use="literal"/>
        </wsdl:input>
      </wsdl:operation>      
      <wsdl:operation name="getWeather">
        <soap:operation soapAction="http://www.example.org/weather/getWeather"/>
        <wsdl:input>
          <soap:body parts="arg" use="literal"/>
        </wsdl:input>
        <wsdl:output>
          <soap:body parts="date temperature wind humidity sky"  use="literal"/>
        </wsdl:output>
      </wsdl:operation>      
      <wsdl:operation name="updateWeather">
        <soap:operation soapAction="http://www.example.org/weather/updateWeather"/>
        <wsdl:output>
          <soap:body parts="arg" use="literal"/>
        </wsdl:output> 
      </wsdl:operation>      
      <wsdl:operation name="alertWeather">
        <soap:operation soapAction="http://www.example.org/weather/alertWeather"/>
        <wsdl:output>
          <soap:body parts="date temperature wind humidity sky" use="literal"/>
        </wsdl:output>
      </wsdl:operation>      
  </wsdl:binding>
```

### Step 6: service definition
```xml
  <wsdl:service name="weather">
    <wsdl:port binding="tns:WeatherBinding" name="WeatherService">
      <!-- extensibility element 5 -->
    </wsdl:port>
  </wsdl:service>
 ``` 
### Step 7: SOAP binding
```xml
  <wsdl:binding type="tns:WeatherPortType" name="WeatherBinding">
      <soap:binding style="document" transport="http://schemas.xmlsoap.org/soap/http"/>
      <wsdl:operation name="subscribeWeather">
        <soap:operation soapAction="http://www.example.org/weather/subscribeWeather"/>
        <wsdl:input>
          <soap:body use="literal"/>
        </wsdl:input>
      </wsdl:operation>
      <wsdl:operation name="getWeather">
        <soap:operation soapAction="http://www.example.org/weather/getWeather"/>
        <wsdl:input>
          <soap:body use="literal"/>
        </wsdl:input>
        <wsdl:output>
          <soap:body use="literal"/>
        </wsdl:output>
      </wsdl:operation>
      <wsdl:operation name="updateWeather">
        <soap:operation soapAction="http://www.example.org/weather/updateWeather"/>
        <wsdl:output>
          <soap:body use="literal"/>
        </wsdl:output>
        <wsdl:input>
          <soap:body use="literal"/>
        </wsdl:input>
      </wsdl:operation>
      <wsdl:operation name="alertWeather">
        <soap:operation soapAction="http://www.example.org/weather/alertWeather"/>
        <wsdl:output>
          <soap:body use="literal"/>
        </wsdl:output>
      </wsdl:operation>
  </wsdl:binding>
   ``` 
   ### Step 8: service binding
   ```xml
  <wsdl:service name="weather">
    <wsdl:port binding="tns:WeatherBinding" name="WeatherService">
      <soap:address location="http://www.example.org/"/>
    </wsdl:port>
  </wsdl:service>
``` 
