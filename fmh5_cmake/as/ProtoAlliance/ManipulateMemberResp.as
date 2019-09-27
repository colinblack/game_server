package com.sanguo.game.server.connectlogic.common.message.ProtoAlliance
{
	import laya.utils.Byte;
	public class ManipulateMemberResp
	{
		public static const PROTO:String = "ProtoAlliance.ManipulateMemberResp";
		public var package_root:*;
		public  var message:*;
		public var member:AllianceMemberCPP;
		public function ManipulateMemberResp(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			member = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.member = this.member.serialize();
			return serializeObj;
		}
		public function unserialize(msgObj:*):ManipulateMemberResp
		{
			member = undefined;
			this.member = new AllianceMemberCPP(package_root).unserialize(msgObj.member);
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ManipulateMemberResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}