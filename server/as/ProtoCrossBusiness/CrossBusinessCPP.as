package ProtoCrossBusiness {
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
	public dynamic final class CrossBusinessCPP extends com.netease.protobuf.Message {
		/**
		 *  @private
		 */
		public static const REFRESHTS:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoCrossBusiness.CrossBusinessCPP.refreshts", "refreshts", (1 << 3) | com.netease.protobuf.WireType.VARINT);

		public var refreshts:uint;

		/**
		 *  @private
		 */
		public static const SLOT1:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoCrossBusiness.CrossBusinessCPP.slot1", "slot1", (2 << 3) | com.netease.protobuf.WireType.VARINT);

		public var slot1:uint;

		/**
		 *  @private
		 */
		public static const SLOT2:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoCrossBusiness.CrossBusinessCPP.slot2", "slot2", (3 << 3) | com.netease.protobuf.WireType.VARINT);

		public var slot2:uint;

		/**
		 *  @private
		 */
		public static const SLOT3:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoCrossBusiness.CrossBusinessCPP.slot3", "slot3", (4 << 3) | com.netease.protobuf.WireType.VARINT);

		public var slot3:uint;

		/**
		 *  @private
		 */
		public static const SLOT4:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoCrossBusiness.CrossBusinessCPP.slot4", "slot4", (5 << 3) | com.netease.protobuf.WireType.VARINT);

		public var slot4:uint;

		/**
		 *  @private
		 */
		public static const SLOT5:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoCrossBusiness.CrossBusinessCPP.slot5", "slot5", (6 << 3) | com.netease.protobuf.WireType.VARINT);

		public var slot5:uint;

		/**
		 *  @private
		 */
		public static const SLOT6:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoCrossBusiness.CrossBusinessCPP.slot6", "slot6", (7 << 3) | com.netease.protobuf.WireType.VARINT);

		public var slot6:uint;

		/**
		 *  @private
		 */
		public static const STATUS:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoCrossBusiness.CrossBusinessCPP.status", "status", (8 << 3) | com.netease.protobuf.WireType.VARINT);

		public var status:uint;

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function writeToBuffer(output:com.netease.protobuf.WritingBuffer):void {
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 1);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.refreshts);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 2);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.slot1);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 3);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.slot2);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 4);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.slot3);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 5);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.slot4);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 6);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.slot5);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 7);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.slot6);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 8);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.status);
			for (var fieldKey:* in this) {
				super.writeUnknown(output, fieldKey);
			}
		}

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function readFromSlice(input:flash.utils.IDataInput, bytesAfterSlice:uint):void {
			var refreshts$count:uint = 0;
			var slot1$count:uint = 0;
			var slot2$count:uint = 0;
			var slot3$count:uint = 0;
			var slot4$count:uint = 0;
			var slot5$count:uint = 0;
			var slot6$count:uint = 0;
			var status$count:uint = 0;
			while (input.bytesAvailable > bytesAfterSlice) {
				var tag:uint = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
				switch (tag >> 3) {
				case 1:
					if (refreshts$count != 0) {
						throw new flash.errors.IOError('Bad data format: CrossBusinessCPP.refreshts cannot be set twice.');
					}
					++refreshts$count;
					this.refreshts = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 2:
					if (slot1$count != 0) {
						throw new flash.errors.IOError('Bad data format: CrossBusinessCPP.slot1 cannot be set twice.');
					}
					++slot1$count;
					this.slot1 = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 3:
					if (slot2$count != 0) {
						throw new flash.errors.IOError('Bad data format: CrossBusinessCPP.slot2 cannot be set twice.');
					}
					++slot2$count;
					this.slot2 = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 4:
					if (slot3$count != 0) {
						throw new flash.errors.IOError('Bad data format: CrossBusinessCPP.slot3 cannot be set twice.');
					}
					++slot3$count;
					this.slot3 = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 5:
					if (slot4$count != 0) {
						throw new flash.errors.IOError('Bad data format: CrossBusinessCPP.slot4 cannot be set twice.');
					}
					++slot4$count;
					this.slot4 = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 6:
					if (slot5$count != 0) {
						throw new flash.errors.IOError('Bad data format: CrossBusinessCPP.slot5 cannot be set twice.');
					}
					++slot5$count;
					this.slot5 = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 7:
					if (slot6$count != 0) {
						throw new flash.errors.IOError('Bad data format: CrossBusinessCPP.slot6 cannot be set twice.');
					}
					++slot6$count;
					this.slot6 = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 8:
					if (status$count != 0) {
						throw new flash.errors.IOError('Bad data format: CrossBusinessCPP.status cannot be set twice.');
					}
					++status$count;
					this.status = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				default:
					super.readUnknown(input, tag);
					break;
				}
			}
		}

	}
}
