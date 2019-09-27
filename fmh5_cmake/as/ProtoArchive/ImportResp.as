package com.sanguo.game.server.connectlogic.common.message.ProtoArchive
{
	import laya.utils.Byte;
	public class ImportResp
	{
		public static const PROTO:String = "ProtoArchive.ImportResp";
		public var package_root:*;
		public  var message:*;
		public var err_msg:Byte;
		public function ImportResp(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			err_msg = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			if(this.err_msg!= undefined)
			{
				serializeObj.err_msg = this.err_msg.getUint8Array(0, this.err_msg.length);
				this.err_msg.pos = 0;
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):ImportResp
		{
			err_msg = undefined;
			if(msgObj.hasOwnProperty("err_msg"))
			{
				this.err_msg = new Byte();
				this.err_msg.writeArrayBuffer(msgObj.err_msg);
				this.err_msg.pos = 0;
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ImportResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}