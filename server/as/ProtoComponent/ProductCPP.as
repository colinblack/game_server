package ProtoComponent {
	import com.netease.protobuf.*;
	use namespace com.netease.protobuf.used_by_generated_code;
	import com.netease.protobuf.fieldDescriptors.*;
	import flash.utils.Endian;
	import flash.utils.IDataInput;
	import flash.utils.IDataOutput;
	import flash.utils.IExternalizable;
	import flash.errors.IOError;
	import ProtoComponent.ComponentCPP;
	// @@protoc_insertion_point(imports)

	// @@protoc_insertion_point(class_metadata)
	public dynamic final class ProductCPP extends com.netease.protobuf.Message {
		/**
		 *  @private
		 */
		public static const MATERIAL:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoComponent.ProductCPP.material", "material", (1 << 3) | com.netease.protobuf.WireType.VARINT);

		private var material$field:uint;

		private var hasField$0:uint = 0;

		public function clearMaterial():void {
			hasField$0 &= 0xfffffffe;
			material$field = new uint();
		}

		public function get hasMaterial():Boolean {
			return (hasField$0 & 0x1) != 0;
		}

		public function set material(value:uint):void {
			hasField$0 |= 0x1;
			material$field = value;
		}

		public function get material():uint {
			return material$field;
		}

		/**
		 *  @private
		 */
		public static const COMPONENT:FieldDescriptor_TYPE_MESSAGE = new FieldDescriptor_TYPE_MESSAGE("ProtoComponent.ProductCPP.component", "component", (2 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, function():Class { return ProtoComponent.ComponentCPP; });

		private var component$field:ProtoComponent.ComponentCPP;

		public function clearComponent():void {
			component$field = null;
		}

		public function get hasComponent():Boolean {
			return component$field != null;
		}

		public function set component(value:ProtoComponent.ComponentCPP):void {
			component$field = value;
		}

		public function get component():ProtoComponent.ComponentCPP {
			return component$field;
		}

		/**
		 *  @private
		 */
		public static const LEVEL:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoComponent.ProductCPP.level", "level", (3 << 3) | com.netease.protobuf.WireType.VARINT);

		public var level:uint;

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function writeToBuffer(output:com.netease.protobuf.WritingBuffer):void {
			if (hasMaterial) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 1);
				com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, material$field);
			}
			if (hasComponent) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 2);
				com.netease.protobuf.WriteUtils.write_TYPE_MESSAGE(output, component$field);
			}
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 3);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.level);
			for (var fieldKey:* in this) {
				super.writeUnknown(output, fieldKey);
			}
		}

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function readFromSlice(input:flash.utils.IDataInput, bytesAfterSlice:uint):void {
			var material$count:uint = 0;
			var component$count:uint = 0;
			var level$count:uint = 0;
			while (input.bytesAvailable > bytesAfterSlice) {
				var tag:uint = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
				switch (tag >> 3) {
				case 1:
					if (material$count != 0) {
						throw new flash.errors.IOError('Bad data format: ProductCPP.material cannot be set twice.');
					}
					++material$count;
					this.material = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 2:
					if (component$count != 0) {
						throw new flash.errors.IOError('Bad data format: ProductCPP.component cannot be set twice.');
					}
					++component$count;
					this.component = new ProtoComponent.ComponentCPP();
					com.netease.protobuf.ReadUtils.read_TYPE_MESSAGE(input, this.component);
					break;
				case 3:
					if (level$count != 0) {
						throw new flash.errors.IOError('Bad data format: ProductCPP.level cannot be set twice.');
					}
					++level$count;
					this.level = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				default:
					super.readUnknown(input, tag);
					break;
				}
			}
		}

	}
}
