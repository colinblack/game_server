package ProtoBattleField {
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
	public dynamic final class SkillOrShapeCity extends com.netease.protobuf.Message {
		/**
		 *  @private
		 */
		public static const HID:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoBattleField.SkillOrShapeCity.hid", "hid", (1 << 3) | com.netease.protobuf.WireType.VARINT);

		public var hid:uint;

		/**
		 *  @private
		 */
		public static const SHAPE:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoBattleField.SkillOrShapeCity.shape", "shape", (2 << 3) | com.netease.protobuf.WireType.VARINT);

		public var shape:uint;

		/**
		 *  @private
		 */
		public static const CID:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoBattleField.SkillOrShapeCity.cid", "cid", (3 << 3) | com.netease.protobuf.WireType.VARINT);

		public var cid:uint;

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function writeToBuffer(output:com.netease.protobuf.WritingBuffer):void {
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 1);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.hid);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 2);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.shape);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 3);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.cid);
			for (var fieldKey:* in this) {
				super.writeUnknown(output, fieldKey);
			}
		}

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function readFromSlice(input:flash.utils.IDataInput, bytesAfterSlice:uint):void {
			var hid$count:uint = 0;
			var shape$count:uint = 0;
			var cid$count:uint = 0;
			while (input.bytesAvailable > bytesAfterSlice) {
				var tag:uint = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
				switch (tag >> 3) {
				case 1:
					if (hid$count != 0) {
						throw new flash.errors.IOError('Bad data format: SkillOrShapeCity.hid cannot be set twice.');
					}
					++hid$count;
					this.hid = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 2:
					if (shape$count != 0) {
						throw new flash.errors.IOError('Bad data format: SkillOrShapeCity.shape cannot be set twice.');
					}
					++shape$count;
					this.shape = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 3:
					if (cid$count != 0) {
						throw new flash.errors.IOError('Bad data format: SkillOrShapeCity.cid cannot be set twice.');
					}
					++cid$count;
					this.cid = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				default:
					super.readUnknown(input, tag);
					break;
				}
			}
		}

	}
}
