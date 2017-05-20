/**
 */
package webApplication.data;

import org.eclipse.emf.ecore.EAttribute;
import org.eclipse.emf.ecore.EClass;
import org.eclipse.emf.ecore.EEnum;
import org.eclipse.emf.ecore.EPackage;
import org.eclipse.emf.ecore.EReference;

import webApplication.WebApplicationPackage;

/**
 * <!-- begin-user-doc -->
 * The <b>Package</b> for the model.
 * It contains accessors for the meta objects to represent
 * <ul>
 *   <li>each class,</li>
 *   <li>each feature of each class,</li>
 *   <li>each operation of each class,</li>
 *   <li>each enum,</li>
 *   <li>and each data type</li>
 * </ul>
 * <!-- end-user-doc -->
 * @see webApplication.data.DataFactory
 * @model kind="package"
 * @generated
 */
public interface DataPackage extends EPackage {
	/**
	 * The package name.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	String eNAME = "data";

	/**
	 * The package namespace URI.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	String eNS_URI = "http://org.disim/WebApplication/data";

	/**
	 * The package namespace name.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	String eNS_PREFIX = "data";

	/**
	 * The singleton instance of the package.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	DataPackage eINSTANCE = webApplication.data.impl.DataPackageImpl.init();

	/**
	 * The meta object id for the '{@link webApplication.data.impl.DataSourceImpl <em>Source</em>}' class.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see webApplication.data.impl.DataSourceImpl
	 * @see webApplication.data.impl.DataPackageImpl#getDataSource()
	 * @generated
	 */
	int DATA_SOURCE = 0;

	/**
	 * The feature id for the '<em><b>Name</b></em>' attribute.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int DATA_SOURCE__NAME = WebApplicationPackage.NAMED__NAME;

	/**
	 * The feature id for the '<em><b>Entity</b></em>' reference.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int DATA_SOURCE__ENTITY = WebApplicationPackage.NAMED_FEATURE_COUNT + 0;

	/**
	 * The number of structural features of the '<em>Source</em>' class.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int DATA_SOURCE_FEATURE_COUNT = WebApplicationPackage.NAMED_FEATURE_COUNT + 1;

	/**
	 * The number of operations of the '<em>Source</em>' class.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int DATA_SOURCE_OPERATION_COUNT = WebApplicationPackage.NAMED_OPERATION_COUNT + 0;

	/**
	 * The meta object id for the '{@link webApplication.data.impl.EntityImpl <em>Entity</em>}' class.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see webApplication.data.impl.EntityImpl
	 * @see webApplication.data.impl.DataPackageImpl#getEntity()
	 * @generated
	 */
	int ENTITY = 1;

	/**
	 * The feature id for the '<em><b>Name</b></em>' attribute.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int ENTITY__NAME = WebApplicationPackage.NAMED__NAME;

	/**
	 * The feature id for the '<em><b>Columns</b></em>' containment reference list.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int ENTITY__COLUMNS = WebApplicationPackage.NAMED_FEATURE_COUNT + 0;

	/**
	 * The feature id for the '<em><b>Relates</b></em>' containment reference list.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int ENTITY__RELATES = WebApplicationPackage.NAMED_FEATURE_COUNT + 1;

	/**
	 * The number of structural features of the '<em>Entity</em>' class.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int ENTITY_FEATURE_COUNT = WebApplicationPackage.NAMED_FEATURE_COUNT + 2;

	/**
	 * The number of operations of the '<em>Entity</em>' class.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int ENTITY_OPERATION_COUNT = WebApplicationPackage.NAMED_OPERATION_COUNT + 0;

	/**
	 * The meta object id for the '{@link webApplication.data.impl.ColumnImpl <em>Column</em>}' class.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see webApplication.data.impl.ColumnImpl
	 * @see webApplication.data.impl.DataPackageImpl#getColumn()
	 * @generated
	 */
	int COLUMN = 2;

	/**
	 * The feature id for the '<em><b>Name</b></em>' attribute.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int COLUMN__NAME = WebApplicationPackage.NAMED__NAME;

	/**
	 * The feature id for the '<em><b>Type</b></em>' attribute.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int COLUMN__TYPE = WebApplicationPackage.NAMED_FEATURE_COUNT + 0;

	/**
	 * The feature id for the '<em><b>Lenght</b></em>' attribute.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int COLUMN__LENGHT = WebApplicationPackage.NAMED_FEATURE_COUNT + 1;

	/**
	 * The feature id for the '<em><b>PK</b></em>' attribute.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int COLUMN__PK = WebApplicationPackage.NAMED_FEATURE_COUNT + 2;

	/**
	 * The number of structural features of the '<em>Column</em>' class.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int COLUMN_FEATURE_COUNT = WebApplicationPackage.NAMED_FEATURE_COUNT + 3;

	/**
	 * The number of operations of the '<em>Column</em>' class.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int COLUMN_OPERATION_COUNT = WebApplicationPackage.NAMED_OPERATION_COUNT + 0;

	/**
	 * The meta object id for the '{@link webApplication.data.impl.RelatedEntityImpl <em>Related Entity</em>}' class.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see webApplication.data.impl.RelatedEntityImpl
	 * @see webApplication.data.impl.DataPackageImpl#getRelatedEntity()
	 * @generated
	 */
	int RELATED_ENTITY = 3;

	/**
	 * The feature id for the '<em><b>Name</b></em>' attribute.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int RELATED_ENTITY__NAME = WebApplicationPackage.NAMED__NAME;

	/**
	 * The feature id for the '<em><b>Relates To</b></em>' reference.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int RELATED_ENTITY__RELATES_TO = WebApplicationPackage.NAMED_FEATURE_COUNT + 0;

	/**
	 * The number of structural features of the '<em>Related Entity</em>' class.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int RELATED_ENTITY_FEATURE_COUNT = WebApplicationPackage.NAMED_FEATURE_COUNT + 1;

	/**
	 * The number of operations of the '<em>Related Entity</em>' class.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int RELATED_ENTITY_OPERATION_COUNT = WebApplicationPackage.NAMED_OPERATION_COUNT + 0;

	/**
	 * The meta object id for the '{@link webApplication.data.ColumnType <em>Column Type</em>}' enum.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see webApplication.data.ColumnType
	 * @see webApplication.data.impl.DataPackageImpl#getColumnType()
	 * @generated
	 */
	int COLUMN_TYPE = 4;


	/**
	 * Returns the meta object for class '{@link webApplication.data.DataSource <em>Source</em>}'.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the meta object for class '<em>Source</em>'.
	 * @see webApplication.data.DataSource
	 * @generated
	 */
	EClass getDataSource();

	/**
	 * Returns the meta object for the reference '{@link webApplication.data.DataSource#getEntity <em>Entity</em>}'.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the meta object for the reference '<em>Entity</em>'.
	 * @see webApplication.data.DataSource#getEntity()
	 * @see #getDataSource()
	 * @generated
	 */
	EReference getDataSource_Entity();

	/**
	 * Returns the meta object for class '{@link webApplication.data.Entity <em>Entity</em>}'.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the meta object for class '<em>Entity</em>'.
	 * @see webApplication.data.Entity
	 * @generated
	 */
	EClass getEntity();

	/**
	 * Returns the meta object for the containment reference list '{@link webApplication.data.Entity#getColumns <em>Columns</em>}'.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the meta object for the containment reference list '<em>Columns</em>'.
	 * @see webApplication.data.Entity#getColumns()
	 * @see #getEntity()
	 * @generated
	 */
	EReference getEntity_Columns();

	/**
	 * Returns the meta object for the containment reference list '{@link webApplication.data.Entity#getRelates <em>Relates</em>}'.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the meta object for the containment reference list '<em>Relates</em>'.
	 * @see webApplication.data.Entity#getRelates()
	 * @see #getEntity()
	 * @generated
	 */
	EReference getEntity_Relates();

	/**
	 * Returns the meta object for class '{@link webApplication.data.Column <em>Column</em>}'.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the meta object for class '<em>Column</em>'.
	 * @see webApplication.data.Column
	 * @generated
	 */
	EClass getColumn();

	/**
	 * Returns the meta object for the attribute '{@link webApplication.data.Column#getType <em>Type</em>}'.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the meta object for the attribute '<em>Type</em>'.
	 * @see webApplication.data.Column#getType()
	 * @see #getColumn()
	 * @generated
	 */
	EAttribute getColumn_Type();

	/**
	 * Returns the meta object for the attribute '{@link webApplication.data.Column#getLenght <em>Lenght</em>}'.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the meta object for the attribute '<em>Lenght</em>'.
	 * @see webApplication.data.Column#getLenght()
	 * @see #getColumn()
	 * @generated
	 */
	EAttribute getColumn_Lenght();

	/**
	 * Returns the meta object for the attribute '{@link webApplication.data.Column#isPK <em>PK</em>}'.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the meta object for the attribute '<em>PK</em>'.
	 * @see webApplication.data.Column#isPK()
	 * @see #getColumn()
	 * @generated
	 */
	EAttribute getColumn_PK();

	/**
	 * Returns the meta object for class '{@link webApplication.data.RelatedEntity <em>Related Entity</em>}'.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the meta object for class '<em>Related Entity</em>'.
	 * @see webApplication.data.RelatedEntity
	 * @generated
	 */
	EClass getRelatedEntity();

	/**
	 * Returns the meta object for the reference '{@link webApplication.data.RelatedEntity#getRelatesTo <em>Relates To</em>}'.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the meta object for the reference '<em>Relates To</em>'.
	 * @see webApplication.data.RelatedEntity#getRelatesTo()
	 * @see #getRelatedEntity()
	 * @generated
	 */
	EReference getRelatedEntity_RelatesTo();

	/**
	 * Returns the meta object for enum '{@link webApplication.data.ColumnType <em>Column Type</em>}'.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the meta object for enum '<em>Column Type</em>'.
	 * @see webApplication.data.ColumnType
	 * @generated
	 */
	EEnum getColumnType();

	/**
	 * Returns the factory that creates the instances of the model.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the factory that creates the instances of the model.
	 * @generated
	 */
	DataFactory getDataFactory();

	/**
	 * <!-- begin-user-doc -->
	 * Defines literals for the meta objects that represent
	 * <ul>
	 *   <li>each class,</li>
	 *   <li>each feature of each class,</li>
	 *   <li>each operation of each class,</li>
	 *   <li>each enum,</li>
	 *   <li>and each data type</li>
	 * </ul>
	 * <!-- end-user-doc -->
	 * @generated
	 */
	interface Literals {
		/**
		 * The meta object literal for the '{@link webApplication.data.impl.DataSourceImpl <em>Source</em>}' class.
		 * <!-- begin-user-doc -->
		 * <!-- end-user-doc -->
		 * @see webApplication.data.impl.DataSourceImpl
		 * @see webApplication.data.impl.DataPackageImpl#getDataSource()
		 * @generated
		 */
		EClass DATA_SOURCE = eINSTANCE.getDataSource();

		/**
		 * The meta object literal for the '<em><b>Entity</b></em>' reference feature.
		 * <!-- begin-user-doc -->
		 * <!-- end-user-doc -->
		 * @generated
		 */
		EReference DATA_SOURCE__ENTITY = eINSTANCE.getDataSource_Entity();

		/**
		 * The meta object literal for the '{@link webApplication.data.impl.EntityImpl <em>Entity</em>}' class.
		 * <!-- begin-user-doc -->
		 * <!-- end-user-doc -->
		 * @see webApplication.data.impl.EntityImpl
		 * @see webApplication.data.impl.DataPackageImpl#getEntity()
		 * @generated
		 */
		EClass ENTITY = eINSTANCE.getEntity();

		/**
		 * The meta object literal for the '<em><b>Columns</b></em>' containment reference list feature.
		 * <!-- begin-user-doc -->
		 * <!-- end-user-doc -->
		 * @generated
		 */
		EReference ENTITY__COLUMNS = eINSTANCE.getEntity_Columns();

		/**
		 * The meta object literal for the '<em><b>Relates</b></em>' containment reference list feature.
		 * <!-- begin-user-doc -->
		 * <!-- end-user-doc -->
		 * @generated
		 */
		EReference ENTITY__RELATES = eINSTANCE.getEntity_Relates();

		/**
		 * The meta object literal for the '{@link webApplication.data.impl.ColumnImpl <em>Column</em>}' class.
		 * <!-- begin-user-doc -->
		 * <!-- end-user-doc -->
		 * @see webApplication.data.impl.ColumnImpl
		 * @see webApplication.data.impl.DataPackageImpl#getColumn()
		 * @generated
		 */
		EClass COLUMN = eINSTANCE.getColumn();

		/**
		 * The meta object literal for the '<em><b>Type</b></em>' attribute feature.
		 * <!-- begin-user-doc -->
		 * <!-- end-user-doc -->
		 * @generated
		 */
		EAttribute COLUMN__TYPE = eINSTANCE.getColumn_Type();

		/**
		 * The meta object literal for the '<em><b>Lenght</b></em>' attribute feature.
		 * <!-- begin-user-doc -->
		 * <!-- end-user-doc -->
		 * @generated
		 */
		EAttribute COLUMN__LENGHT = eINSTANCE.getColumn_Lenght();

		/**
		 * The meta object literal for the '<em><b>PK</b></em>' attribute feature.
		 * <!-- begin-user-doc -->
		 * <!-- end-user-doc -->
		 * @generated
		 */
		EAttribute COLUMN__PK = eINSTANCE.getColumn_PK();

		/**
		 * The meta object literal for the '{@link webApplication.data.impl.RelatedEntityImpl <em>Related Entity</em>}' class.
		 * <!-- begin-user-doc -->
		 * <!-- end-user-doc -->
		 * @see webApplication.data.impl.RelatedEntityImpl
		 * @see webApplication.data.impl.DataPackageImpl#getRelatedEntity()
		 * @generated
		 */
		EClass RELATED_ENTITY = eINSTANCE.getRelatedEntity();

		/**
		 * The meta object literal for the '<em><b>Relates To</b></em>' reference feature.
		 * <!-- begin-user-doc -->
		 * <!-- end-user-doc -->
		 * @generated
		 */
		EReference RELATED_ENTITY__RELATES_TO = eINSTANCE.getRelatedEntity_RelatesTo();

		/**
		 * The meta object literal for the '{@link webApplication.data.ColumnType <em>Column Type</em>}' enum.
		 * <!-- begin-user-doc -->
		 * <!-- end-user-doc -->
		 * @see webApplication.data.ColumnType
		 * @see webApplication.data.impl.DataPackageImpl#getColumnType()
		 * @generated
		 */
		EEnum COLUMN_TYPE = eINSTANCE.getColumnType();

	}

} //DataPackage
