package Common {
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
	public dynamic final class Login extends com.netease.protobuf.Message {
		/**
		 *  @private
		 */
		public static const UID:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("Common.Login.uid", "uid", (1 << 3) | com.netease.protobuf.WireType.VARINT);

		public var uid:uint;

		/**
		 *  @private
		 */
		public static const OPENID:FieldDescriptor_TYPE_STRING = new FieldDescriptor_TYPE_STRING("Common.Login.openid", "openid", (2 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED);

		public var openid:String;

		/**
		 *  @private
		 */
		public static const OPENKEY:FieldDescriptor_TYPE_STRING = new FieldDescriptor_TYPE_STRING("Common.Login.openkey", "openkey", (3 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED);

		public var openkey:String;

		/**
		 *  @private
		 */
		public static const TS:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("Common.Login.ts", "ts", (4 << 3) | com.netease.protobuf.WireType.VARINT);

		public var ts:uint;

		/**
		 *  @private
		 */
		public static const SIG:FieldDescriptor_TYPE_STRING = new FieldDescriptor_TYPE_STRING("Common.Login.sig", "sig", (5 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED);

		public var sig:String;

		/**
		 *  @private
		 */
		public static const ISNEW:FieldDescriptor_TYPE_BOOL = new FieldDescriptor_TYPE_BOOL("Common.Login.isnew", "isnew", (6 << 3) | com.netease.protobuf.WireType.VARINT);

		public var isnew:Boolean;

		/**
		 *  @private
		 */
		public static const PLATFORM:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("Common.Login.platform", "platform", (7 << 3) | com.netease.protobuf.WireType.VARINT);

		public var platform:uint;

		/**
		 *  @private
		 */
		public static const FIG:FieldDescriptor_TYPE_STRING = new FieldDescriptor_TYPE_STRING("Common.Login.fig", "fig", (8 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED);

		private var fig$field:String;

		public function clearFig():void {
			fig$field = null;
		}

		public function get hasFig():Boolean {
			return fig$field != null;
		}

		public function set fig(value:String):void {
			fig$field = value;
		}

		public function get fig():String {
			return fig$field;
		}

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function writeToBuffer(output:com.netease.protobuf.WritingBuffer):void {
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 1);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.uid);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 2);
			com.netease.protobuf.WriteUtils.write_TYPE_STRING(output, this.openid);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 3);
			com.netease.protobuf.WriteUtils.write_TYPE_STRING(output, this.openkey);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 4);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.ts);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 5);
			com.netease.protobuf.WriteUtils.write_TYPE_STRING(output, this.sig);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 6);
			com.netease.protobuf.WriteUtils.write_TYPE_BOOL(output, this.isnew);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 7);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.platform);
			if (hasFig) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 8);
				com.netease.protobuf.WriteUtils.write_TYPE_STRING(output, fig$field);
			}
			for (var fieldKey:* in this) {
				super.writeUnknown(output, fieldKey);
			}
		}

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function readFromSlice(input:flash.utils.IDataInput, bytesAfterSlice:uint):void {
			var uid$count:uint = 0;
			var openid$count:uint = 0;
			var openkey$count:uint = 0;
			var ts$count:uint = 0;
			var sig$count:uint = 0;
			var isnew$count:uint = 0;
			var platform$count:uint = 0;
			var fig$count:uint = 0;
			while (input.bytesAvailable > bytesAfterSlice) {
				var tag:uint = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
				switch (tag >> 3) {
				case 1:
					if (uid$count != 0) {
						throw new flash.errors.IOError('Bad data format: Login.uid cannot be set twice.');
					}
					++uid$count;
					this.uid = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 2:
					if (openid$count != 0) {
						throw new flash.errors.IOError('Bad data format: Login.openid cannot be set twice.');
					}
					++openid$count;
					this.openid = com.netease.protobuf.ReadUtils.read_TYPE_STRING(input);
					break;
				case 3:
					if (openkey$count != 0) {
						throw new flash.errors.IOError('Bad data format: Login.openkey cannot be set twice.');
					}
					++openkey$count;
					this.openkey = com.netease.protobuf.ReadUtils.read_TYPE_STRING(input);
					break;
				case 4:
					if (ts$count != 0) {
						throw new flash.errors.IOError('Bad data format: Login.ts cannot be set twice.');
					}
					++ts$count;
					this.ts = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 5:
					if (sig$count != 0) {
						throw new flash.errors.IOError('Bad data format: Login.sig cannot be set twice.');
					}
					++sig$count;
					this.sig = com.netease.protobuf.ReadUtils.read_TYPE_STRING(input);
					break;
				case 6:
					if (isnew$count != 0) {
						throw new flash.errors.IOError('Bad data format: Login.isnew cannot be set twice.');
					}
					++isnew$count;
					this.isnew = com.netease.protobuf.ReadUtils.read_TYPE_BOOL(input);
					break;
				case 7:
					if (platform$count != 0) {
						throw new flash.errors.IOError('Bad data format: Login.platform cannot be set twice.');
					}
					++platform$count;
					this.platform = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 8:
					if (fig$count != 0) {
						throw new flash.errors.IOError('Bad data format: Login.fig cannot be set twice.');
					}
					++fig$count;
					this.fig = com.netease.protobuf.ReadUtils.read_TYPE_STRING(input);
					break;
				default:
					super.readUnknown(input, tag);
					break;
				}
			}
		}

	}
}
