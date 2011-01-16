#ifndef CITY_H
#define CITY_H

/** 
 * \file City.h
 * \authors Neil Conlan
 * \date 6 April 2006
 */

/**
 * An instance is a city with x, y, z coordinates.
 */
class City
{
public:
	/**
     * City default constructor.
     */
	City();
	/**
     * City copy constructor.
	 * \param other is the other city to copy.
     */
	City(const City & other);
	/**
     * City copy constructor.
	 * \param x is the x position of the city
	 * \param y is the y position of the city
	 * \param z is the z position of the city
     */
	City(int x, int y, int z);
	/**
     * City destructor
     */
	~City();

	/**
     * Sets the coordinates of the city.
	 * \param x is the x position of the city
	 * \param y is the y position of the city
	 * \param z is the z position of the city
     */
	void setCoordinates(int x, int y, int z);

	/**
     * Gets the x position.
	 * \return is the x position of the city
     */
	int getX() const;
	/**
     * Gets the y position.
	 * \return is the y position of the city
     */
	int getY() const;
	/**
     * Gets the z position.
	 * \return is the z position of the city
     */
	int getZ() const;

	/**
     * Function to check if two cities are equal.
	 * \param c1 is the first city.
	 * \param c2 is the second city.
	 * \return bool indicated if they are equal or not.
     */
	friend bool operator==(const City & c1, const City & c2);
	/**
     * Function to check if two cities are not equal.
	 * \param c1 is the first city.
	 * \param c2 is the second city.
	 * \return bool indicated if they are not equal or not.
     */
	friend bool operator!=(const City & c1, const City & c2);
	
private:
	/**
     * x position of the city
     */
	int x;
	/**
     * y position of the city
     */
	int y;
	/**
     * z position of the city
     */
	int z;

};

#endif