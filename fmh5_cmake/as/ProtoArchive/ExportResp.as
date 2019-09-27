package com.sanguo.game.server.connectlogic.common.message.ProtoArchive
{
	import laya.utils.Byte;
	public class ExportResp
	{
		public static const PROTO:String = "ProtoArchive.ExportResp";
		public var package_root:*;
		public  var message:*;
		public var data:UserData;
		public var err_msg:String;
		public function ExportResp(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			data = undefined;
			err_msg = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			if(this.data!= undefined)
			{
				serializeObj.data = this.data.serialize();
			}
			if(this.err_msg!= undefined)
			{
				serializeObj.err_msg = this.err_msg;
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):ExportResp
		{
			data = undefined;
			err_msg = undefined;
			if(msgObj.hasOwnProperty("data"))
			{
				this.data = new UserData(package_root).unserialize(msgObj.data);
			}
			if(msgObj.hasOwnProperty("err_msg"))
			{
				this.err_msg = msgObj.err_msg;
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ExportResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}