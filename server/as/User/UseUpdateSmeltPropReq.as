package User {
	import com.netease.protobuf.*;
	use namespace com.netease.protobuf.used_by_generated_code;
	import com.netease.protobuf.fieldDescriptors.*;
	import flash.utils.Endian;
	import flash.utils.IDataInput;
	import flash.utils.IDataOutput;
	import flash.utils.IExternalizable;
	import flash.errors.IOError;
	// @@protoc_insertion_point(imports)

	// @@protoc_insertion_point(class_metadata)
	public dynamic final class UseUpdateSmeltPropReq extends com.netease.protobuf.Message {
		/**
		 *  @private
		 */
		public static const PROP_ID:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("User.UseUpdateSmeltPropReq.prop_id", "propId", (1 << 3) | com.netease.protobuf.WireType.VARINT);

		public var propId:uint;

		/**
		 *  @private
		 */
		public static const PROP_UD:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("User.UseUpdateSmeltPropReq.prop_ud", "propUd", (2 << 3) | com.netease.protobuf.WireType.VARINT);

		public var propUd:uint;

		/**
		 *  @private
		 */
		public static const EQUIP_UD:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("User.UseUpdateSmeltPropReq.equip_ud", "equipUd", (3 << 3) | com.netease.protobuf.WireType.VARINT);

		public var equipUd:uint;

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function writeToBuffer(output:com.netease.protobuf.WritingBuffer):void {
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 1);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.propId);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 2);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.propUd);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 3);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.equipUd);
			for (var fieldKey:* in this) {
				super.writeUnknown(output, fieldKey);
			}
		}

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function readFromSlice(input:flash.utils.IDataInput, bytesAfterSlice:uint):void {
			var prop_id$count:uint = 0;
			var prop_ud$count:uint = 0;
			var equip_ud$count:uint = 0;
			while (input.bytesAvailable > bytesAfterSlice) {
				var tag:uint = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
				switch (tag >> 3) {
				case 1:
					if (prop_id$count != 0) {
						throw new flash.errors.IOError('Bad data format: UseUpdateSmeltPropReq.propId cannot be set twice.');
					}
					++prop_id$count;
					this.propId = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 2:
					if (prop_ud$count != 0) {
						throw new flash.errors.IOError('Bad data format: UseUpdateSmeltPropReq.propUd cannot be set twice.');
					}
					++prop_ud$count;
					this.propUd = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 3:
					if (equip_ud$count != 0) {
						throw new flash.errors.IOError('Bad data format: UseUpdateSmeltPropReq.equipUd cannot be set twice.');
					}
					++equip_ud$count;
					this.equipUd = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				default:
					super.readUnknown(input, tag);
					break;
				}
			}
		}

	}
}
