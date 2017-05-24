/**
 */
package webApplication.content;

import webApplication.Named;

import webApplication.data.DataSource;

/**
 * <!-- begin-user-doc -->
 * A representation of the model object '<em><b>Content</b></em>'.
 * <!-- end-user-doc -->
 *
 * <p>
 * The following features are supported:
 * </p>
 * <ul>
 *   <li>{@link webApplication.content.Content#getDataSource <em>Data Source</em>}</li>
 * </ul>
 *
 * @see webApplication.content.ContentPackage#getContent()
 * @model abstract="true"
 * @generated
 */
public interface Content extends Named {
	/**
	 * Returns the value of the '<em><b>Data Source</b></em>' reference.
	 * <!-- begin-user-doc -->
	 * <p>
	 * If the meaning of the '<em>Data Source</em>' reference isn't clear,
	 * there really should be more of a description here...
	 * </p>
	 * <!-- end-user-doc -->
	 * @return the value of the '<em>Data Source</em>' reference.
	 * @see #setDataSource(DataSource)
	 * @see webApplication.content.ContentPackage#getContent_DataSource()
	 * @model required="true"
	 * @generated
	 */
	DataSource getDataSource();

	/**
	 * Sets the value of the '{@link webApplication.content.Content#getDataSource <em>Data Source</em>}' reference.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @param value the new value of the '<em>Data Source</em>' reference.
	 * @see #getDataSource()
	 * @generated
	 */
	void setDataSource(DataSource value);

} // Content
