package ProtoNPCActivity {
	import com.netease.protobuf.*;
	use namespace com.netease.protobuf.used_by_generated_code;
	import com.netease.protobuf.fieldDescriptors.*;
	import flash.utils.Endian;
	import flash.utils.IDataInput;
	import flash.utils.IDataOutput;
	import flash.utils.IExternalizable;
	import flash.errors.IOError;
	import DataConfig.RewardConfigCPP;
	// @@protoc_insertion_point(imports)

	// @@protoc_insertion_point(class_metadata)
	public dynamic final class OpenPlatformAffairConfigCPP extends com.netease.protobuf.Message {
		/**
		 *  @private
		 */
		public static const STARTDAY:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoNPCActivity.OpenPlatformAffairConfigCPP.startday", "startday", (1 << 3) | com.netease.protobuf.WireType.VARINT);

		public var startday:uint;

		/**
		 *  @private
		 */
		public static const REWARD:RepeatedFieldDescriptor_TYPE_MESSAGE = new RepeatedFieldDescriptor_TYPE_MESSAGE("ProtoNPCActivity.OpenPlatformAffairConfigCPP.reward", "reward", (2 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, function():Class { return DataConfig.RewardConfigCPP; });

		[ArrayElementType("DataConfig.RewardConfigCPP")]
		public var reward:Array = [];

		/**
		 *  @private
		 */
		public static const ACTIVE_VALUE:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoNPCActivity.OpenPlatformAffairConfigCPP.active_value", "activeValue", (3 << 3) | com.netease.protobuf.WireType.VARINT);

		public var activeValue:uint;

		/**
		 *  @private
		 */
		public static const PAYCASH:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoNPCActivity.OpenPlatformAffairConfigCPP.paycash", "paycash", (4 << 3) | com.netease.protobuf.WireType.VARINT);

		private var paycash$field:uint;

		private var hasField$0:uint = 0;

		public function clearPaycash():void {
			hasField$0 &= 0xfffffffe;
			paycash$field = new uint();
		}

		public function get hasPaycash():Boolean {
			return (hasField$0 & 0x1) != 0;
		}

		public function set paycash(value:uint):void {
			hasField$0 |= 0x1;
			paycash$field = value;
		}

		public function get paycash():uint {
			return paycash$field;
		}

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function writeToBuffer(output:com.netease.protobuf.WritingBuffer):void {
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 1);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.startday);
			for (var reward$index:uint = 0; reward$index < this.reward.length; ++reward$index) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 2);
				com.netease.protobuf.WriteUtils.write_TYPE_MESSAGE(output, this.reward[reward$index]);
			}
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 3);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.activeValue);
			if (hasPaycash) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 4);
				com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, paycash$field);
			}
			for (var fieldKey:* in this) {
				super.writeUnknown(output, fieldKey);
			}
		}

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function readFromSlice(input:flash.utils.IDataInput, bytesAfterSlice:uint):void {
			var startday$count:uint = 0;
			var active_value$count:uint = 0;
			var paycash$count:uint = 0;
			while (input.bytesAvailable > bytesAfterSlice) {
				var tag:uint = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
				switch (tag >> 3) {
				case 1:
					if (startday$count != 0) {
						throw new flash.errors.IOError('Bad data format: OpenPlatformAffairConfigCPP.startday cannot be set twice.');
					}
					++startday$count;
					this.startday = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 2:
					this.reward.push(com.netease.protobuf.ReadUtils.read_TYPE_MESSAGE(input, new DataConfig.RewardConfigCPP()));
					break;
				case 3:
					if (active_value$count != 0) {
						throw new flash.errors.IOError('Bad data format: OpenPlatformAffairConfigCPP.activeValue cannot be set twice.');
					}
					++active_value$count;
					this.activeValue = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 4:
					if (paycash$count != 0) {
						throw new flash.errors.IOError('Bad data format: OpenPlatformAffairConfigCPP.paycash cannot be set twice.');
					}
					++paycash$count;
					this.paycash = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				default:
					super.readUnknown(input, tag);
					break;
				}
			}
		}

	}
}
