package com.sanguo.game.server.connectlogic.common.message.ProtoActivity
{
	import laya.utils.Byte;
	public class NewShareResp
	{
		public static const PROTO:String = "ProtoActivity.NewShareResp";
		public var package_root:*;
		public  var message:*;
		public var common:CommonItemsCPP;
		public var newShare:NewShareCPP;
		public function NewShareResp(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			common = undefined;
			newShare = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.common = this.common.serialize();
			serializeObj.newShare = this.newShare.serialize();
			return serializeObj;
		}
		public function unserialize(msgObj:*):NewShareResp
		{
			common = undefined;
			newShare = undefined;
			this.common = new CommonItemsCPP(package_root).unserialize(msgObj.common);
			this.newShare = new NewShareCPP(package_root).unserialize(msgObj.newShare);
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):NewShareResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}