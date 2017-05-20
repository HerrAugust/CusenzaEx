/**
 */
package webApplication;

import org.eclipse.emf.common.util.EList;

import webApplication.content.Page;

import webApplication.data.DataSource;
import webApplication.data.Entity;

/**
 * <!-- begin-user-doc -->
 * A representation of the model object '<em><b>Model</b></em>'.
 * <!-- end-user-doc -->
 *
 * <p>
 * The following features are supported:
 * </p>
 * <ul>
 *   <li>{@link webApplication.WebApplicationModel#getEntities <em>Entities</em>}</li>
 *   <li>{@link webApplication.WebApplicationModel#getDataSources <em>Data Sources</em>}</li>
 *   <li>{@link webApplication.WebApplicationModel#getPages <em>Pages</em>}</li>
 * </ul>
 *
 * @see webApplication.WebApplicationPackage#getWebApplicationModel()
 * @model
 * @generated
 */
public interface WebApplicationModel extends Named {
	/**
	 * Returns the value of the '<em><b>Entities</b></em>' containment reference list.
	 * The list contents are of type {@link webApplication.data.Entity}.
	 * <!-- begin-user-doc -->
	 * <p>
	 * If the meaning of the '<em>Entities</em>' containment reference list isn't clear,
	 * there really should be more of a description here...
	 * </p>
	 * <!-- end-user-doc -->
	 * @return the value of the '<em>Entities</em>' containment reference list.
	 * @see webApplication.WebApplicationPackage#getWebApplicationModel_Entities()
	 * @model containment="true"
	 * @generated
	 */
	EList<Entity> getEntities();

	/**
	 * Returns the value of the '<em><b>Data Sources</b></em>' containment reference list.
	 * The list contents are of type {@link webApplication.data.DataSource}.
	 * <!-- begin-user-doc -->
	 * <p>
	 * If the meaning of the '<em>Data Sources</em>' containment reference list isn't clear,
	 * there really should be more of a description here...
	 * </p>
	 * <!-- end-user-doc -->
	 * @return the value of the '<em>Data Sources</em>' containment reference list.
	 * @see webApplication.WebApplicationPackage#getWebApplicationModel_DataSources()
	 * @model containment="true"
	 * @generated
	 */
	EList<DataSource> getDataSources();

	/**
	 * Returns the value of the '<em><b>Pages</b></em>' containment reference list.
	 * The list contents are of type {@link webApplication.content.Page}.
	 * <!-- begin-user-doc -->
	 * <p>
	 * If the meaning of the '<em>Pages</em>' containment reference list isn't clear,
	 * there really should be more of a description here...
	 * </p>
	 * <!-- end-user-doc -->
	 * @return the value of the '<em>Pages</em>' containment reference list.
	 * @see webApplication.WebApplicationPackage#getWebApplicationModel_Pages()
	 * @model containment="true"
	 * @generated
	 */
	EList<Page> getPages();

} // WebApplicationModel
