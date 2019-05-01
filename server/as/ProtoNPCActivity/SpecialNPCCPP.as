package ProtoNPCActivity {
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
	public dynamic final class SpecialNPCCPP extends com.netease.protobuf.Message {
		/**
		 *  @private
		 */
		public static const KINDOM:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoNPCActivity.SpecialNPCCPP.kindom", "kindom", (1 << 3) | com.netease.protobuf.WireType.VARINT);

		public var kindom:uint;

		/**
		 *  @private
		 */
		public static const CITY:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoNPCActivity.SpecialNPCCPP.city", "city", (2 << 3) | com.netease.protobuf.WireType.VARINT);

		public var city:uint;

		/**
		 *  @private
		 */
		public static const NEXTTS:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoNPCActivity.SpecialNPCCPP.nextts", "nextts", (3 << 3) | com.netease.protobuf.WireType.VARINT);

		public var nextts:uint;

		/**
		 *  @private
		 */
		public static const NPCID:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoNPCActivity.SpecialNPCCPP.npcid", "npcid", (4 << 3) | com.netease.protobuf.WireType.VARINT);

		public var npcid:uint;

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function writeToBuffer(output:com.netease.protobuf.WritingBuffer):void {
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 1);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.kindom);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 2);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.city);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 3);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.nextts);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 4);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.npcid);
			for (var fieldKey:* in this) {
				super.writeUnknown(output, fieldKey);
			}
		}

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function readFromSlice(input:flash.utils.IDataInput, bytesAfterSlice:uint):void {
			var kindom$count:uint = 0;
			var city$count:uint = 0;
			var nextts$count:uint = 0;
			var npcid$count:uint = 0;
			while (input.bytesAvailable > bytesAfterSlice) {
				var tag:uint = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
				switch (tag >> 3) {
				case 1:
					if (kindom$count != 0) {
						throw new flash.errors.IOError('Bad data format: SpecialNPCCPP.kindom cannot be set twice.');
					}
					++kindom$count;
					this.kindom = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 2:
					if (city$count != 0) {
						throw new flash.errors.IOError('Bad data format: SpecialNPCCPP.city cannot be set twice.');
					}
					++city$count;
					this.city = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 3:
					if (nextts$count != 0) {
						throw new flash.errors.IOError('Bad data format: SpecialNPCCPP.nextts cannot be set twice.');
					}
					++nextts$count;
					this.nextts = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 4:
					if (npcid$count != 0) {
						throw new flash.errors.IOError('Bad data format: SpecialNPCCPP.npcid cannot be set twice.');
					}
					++npcid$count;
					this.npcid = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				default:
					super.readUnknown(input, tag);
					break;
				}
			}
		}

	}
}
