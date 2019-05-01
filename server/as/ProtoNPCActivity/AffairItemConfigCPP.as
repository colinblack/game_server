package ProtoNPCActivity {
	import com.netease.protobuf.*;
	use namespace com.netease.protobuf.used_by_generated_code;
	import com.netease.protobuf.fieldDescriptors.*;
	import flash.utils.Endian;
	import flash.utils.IDataInput;
	import flash.utils.IDataOutput;
	import flash.utils.IExternalizable;
	import flash.errors.IOError;
	import ProtoNPCActivity.OpenPlatformAffairConfigCPP;
	// @@protoc_insertion_point(imports)

	// @@protoc_insertion_point(class_metadata)
	public dynamic final class AffairItemConfigCPP extends com.netease.protobuf.Message {
		/**
		 *  @private
		 */
		public static const PROPS:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoNPCActivity.AffairItemConfigCPP.props", "props", (1 << 3) | com.netease.protobuf.WireType.VARINT);

		private var props$field:uint;

		private var hasField$0:uint = 0;

		public function clearProps():void {
			hasField$0 &= 0xfffffffe;
			props$field = new uint();
		}

		public function get hasProps():Boolean {
			return (hasField$0 & 0x1) != 0;
		}

		public function set props(value:uint):void {
			hasField$0 |= 0x1;
			props$field = value;
		}

		public function get props():uint {
			return props$field;
		}

		/**
		 *  @private
		 */
		public static const COUNT:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoNPCActivity.AffairItemConfigCPP.count", "count", (2 << 3) | com.netease.protobuf.WireType.VARINT);

		private var count$field:uint;

		public function clearCount():void {
			hasField$0 &= 0xfffffffd;
			count$field = new uint();
		}

		public function get hasCount():Boolean {
			return (hasField$0 & 0x2) != 0;
		}

		public function set count(value:uint):void {
			hasField$0 |= 0x2;
			count$field = value;
		}

		public function get count():uint {
			return count$field;
		}

		/**
		 *  @private
		 */
		public static const OPEN_PLATFORM_AFFAIR:RepeatedFieldDescriptor_TYPE_MESSAGE = new RepeatedFieldDescriptor_TYPE_MESSAGE("ProtoNPCActivity.AffairItemConfigCPP.open_platform_affair", "openPlatformAffair", (3 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, function():Class { return ProtoNPCActivity.OpenPlatformAffairConfigCPP; });

		[ArrayElementType("ProtoNPCActivity.OpenPlatformAffairConfigCPP")]
		public var openPlatformAffair:Array = [];

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function writeToBuffer(output:com.netease.protobuf.WritingBuffer):void {
			if (hasProps) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 1);
				com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, props$field);
			}
			if (hasCount) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 2);
				com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, count$field);
			}
			for (var openPlatformAffair$index:uint = 0; openPlatformAffair$index < this.openPlatformAffair.length; ++openPlatformAffair$index) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 3);
				com.netease.protobuf.WriteUtils.write_TYPE_MESSAGE(output, this.openPlatformAffair[openPlatformAffair$index]);
			}
			for (var fieldKey:* in this) {
				super.writeUnknown(output, fieldKey);
			}
		}

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function readFromSlice(input:flash.utils.IDataInput, bytesAfterSlice:uint):void {
			var props$count:uint = 0;
			var count$count:uint = 0;
			while (input.bytesAvailable > bytesAfterSlice) {
				var tag:uint = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
				switch (tag >> 3) {
				case 1:
					if (props$count != 0) {
						throw new flash.errors.IOError('Bad data format: AffairItemConfigCPP.props cannot be set twice.');
					}
					++props$count;
					this.props = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 2:
					if (count$count != 0) {
						throw new flash.errors.IOError('Bad data format: AffairItemConfigCPP.count cannot be set twice.');
					}
					++count$count;
					this.count = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 3:
					this.openPlatformAffair.push(com.netease.protobuf.ReadUtils.read_TYPE_MESSAGE(input, new ProtoNPCActivity.OpenPlatformAffairConfigCPP()));
					break;
				default:
					super.readUnknown(input, tag);
					break;
				}
			}
		}

	}
}
