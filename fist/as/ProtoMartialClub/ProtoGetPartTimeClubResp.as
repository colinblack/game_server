package com.sanguo.game.server.connectlogic.common.message.ProtoMartialClub
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class ProtoGetPartTimeClubResp
	{
		public static const PROTO:String = "ProtoMartialClub.ProtoGetPartTimeClubResp";
		public var package_root:*;
		public  var message:*;
		public var info:Vector.<SingleMartialClub>;
		public function ProtoGetPartTimeClubResp(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
			info = new Vector.<SingleMartialClub>();
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.info = [];
			for(var i:int = 0;i < this.info.length;i++)
			{
				serializeObj.info.push(this.info[i].serialize());
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):ProtoGetPartTimeClubResp
		{
			info = new Vector.<SingleMartialClub>();
			for(var i:int = 0;i < msgObj.info.length;i++)
			{
				this.info.push(new SingleMartialClub(package_root).unserialize(msgObj.info[i]));
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ProtoGetPartTimeClubResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}