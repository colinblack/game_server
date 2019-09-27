package com.sanguo.game.server.connectlogic.common.message.ProtoRotaryTable
{
	import laya.utils.Byte;
	public class ShareResp
	{
		public static const PROTO:String = "ProtoRotaryTable.ShareResp";
		public var package_root:*;
		public  var message:*;
		public var drawinfo:DrawCntCPP;
		public function ShareResp(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			drawinfo = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.drawinfo = this.drawinfo.serialize();
			return serializeObj;
		}
		public function unserialize(msgObj:*):ShareResp
		{
			drawinfo = undefined;
			this.drawinfo = new DrawCntCPP(package_root).unserialize(msgObj.drawinfo);
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ShareResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}