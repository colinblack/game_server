package ProtoBuilding {
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
	public dynamic final class BuildUnlockReq extends com.netease.protobuf.Message {
		/**
		 *  @private
		 */
		public static const IDS:RepeatedFieldDescriptor_TYPE_UINT32 = new RepeatedFieldDescriptor_TYPE_UINT32("ProtoBuilding.BuildUnlockReq.ids", "ids", (1 << 3) | com.netease.protobuf.WireType.VARINT);

		[ArrayElementType("uint")]
		public var ids:Array = [];

		/**
		 *  @private
		 */
		public static const LOCK_QUEUE:FieldDescriptor_TYPE_BOOL = new FieldDescriptor_TYPE_BOOL("ProtoBuilding.BuildUnlockReq.lock_queue", "lockQueue", (2 << 3) | com.netease.protobuf.WireType.VARINT);

		private var lock_queue$field:Boolean;

		private var hasField$0:uint = 0;

		public function clearLockQueue():void {
			hasField$0 &= 0xfffffffe;
			lock_queue$field = new Boolean();
		}

		public function get hasLockQueue():Boolean {
			return (hasField$0 & 0x1) != 0;
		}

		public function set lockQueue(value:Boolean):void {
			hasField$0 |= 0x1;
			lock_queue$field = value;
		}

		public function get lockQueue():Boolean {
			return lock_queue$field;
		}

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function writeToBuffer(output:com.netease.protobuf.WritingBuffer):void {
			for (var ids$index:uint = 0; ids$index < this.ids.length; ++ids$index) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 1);
				com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.ids[ids$index]);
			}
			if (hasLockQueue) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 2);
				com.netease.protobuf.WriteUtils.write_TYPE_BOOL(output, lock_queue$field);
			}
			for (var fieldKey:* in this) {
				super.writeUnknown(output, fieldKey);
			}
		}

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function readFromSlice(input:flash.utils.IDataInput, bytesAfterSlice:uint):void {
			var lock_queue$count:uint = 0;
			while (input.bytesAvailable > bytesAfterSlice) {
				var tag:uint = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
				switch (tag >> 3) {
				case 1:
					if ((tag & 7) == com.netease.protobuf.WireType.LENGTH_DELIMITED) {
						com.netease.protobuf.ReadUtils.readPackedRepeated(input, com.netease.protobuf.ReadUtils.read_TYPE_UINT32, this.ids);
						break;
					}
					this.ids.push(com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input));
					break;
				case 2:
					if (lock_queue$count != 0) {
						throw new flash.errors.IOError('Bad data format: BuildUnlockReq.lockQueue cannot be set twice.');
					}
					++lock_queue$count;
					this.lockQueue = com.netease.protobuf.ReadUtils.read_TYPE_BOOL(input);
					break;
				default:
					super.readUnknown(input, tag);
					break;
				}
			}
		}

	}
}
