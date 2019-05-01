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
	public dynamic final class RequestList extends com.netease.protobuf.Message {
		/**
		 *  @private
		 */
		public static const CID:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoBattleField.RequestList.cid", "cid", (1 << 3) | com.netease.protobuf.WireType.VARINT);

		public var cid:uint;

		/**
		 *  @private
		 */
		public static const ATTACK:FieldDescriptor_TYPE_BOOL = new FieldDescriptor_TYPE_BOOL("ProtoBattleField.RequestList.attack", "attack", (2 << 3) | com.netease.protobuf.WireType.VARINT);

		public var attack:Boolean;

		/**
		 *  @private
		 */
		public static const PAGE:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoBattleField.RequestList.page", "page", (3 << 3) | com.netease.protobuf.WireType.VARINT);

		public var page:uint;

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function writeToBuffer(output:com.netease.protobuf.WritingBuffer):void {
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 1);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.cid);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 2);
			com.netease.protobuf.WriteUtils.write_TYPE_BOOL(output, this.attack);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 3);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.page);
			for (var fieldKey:* in this) {
				super.writeUnknown(output, fieldKey);
			}
		}

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function readFromSlice(input:flash.utils.IDataInput, bytesAfterSlice:uint):void {
			var cid$count:uint = 0;
			var attack$count:uint = 0;
			var page$count:uint = 0;
			while (input.bytesAvailable > bytesAfterSlice) {
				var tag:uint = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
				switch (tag >> 3) {
				case 1:
					if (cid$count != 0) {
						throw new flash.errors.IOError('Bad data format: RequestList.cid cannot be set twice.');
					}
					++cid$count;
					this.cid = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 2:
					if (attack$count != 0) {
						throw new flash.errors.IOError('Bad data format: RequestList.attack cannot be set twice.');
					}
					++attack$count;
					this.attack = com.netease.protobuf.ReadUtils.read_TYPE_BOOL(input);
					break;
				case 3:
					if (page$count != 0) {
						throw new flash.errors.IOError('Bad data format: RequestList.page cannot be set twice.');
					}
					++page$count;
					this.page = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				default:
					super.readUnknown(input, tag);
					break;
				}
			}
		}

	}
}
